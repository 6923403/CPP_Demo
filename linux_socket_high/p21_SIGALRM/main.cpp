#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <assert.h>
#include <signal.h>

#include "lst_timer.h"

const int FD_LIMIT = 65535;                  //客户端最大连接数
const int MAX_EVENT_NUMBER = 1024;
const int TIMESLOT = 5;                      //定时器的超时时间

static int pipefd[2];
static sort_timer_lst timer_lst;
static int epollfd = 0;

int setnonblocking(int fd) //设置非阻塞
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_GETFL, new_option);

}

void addfd(int epollfd, int fd) //添加描述符事件
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

void sig_handler(int sig)
{
    int error = errno;
    int msg = sig;
    send(pipefd[1], (char*)&msg, 1, 0);
    errno = error;
}

void addsig(int sig)
{
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;

    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

void timer_handler()
{
    timer_lst.tick();

    //因为一次alarm调用只会触发一次，所以要重新设定
    alarm(TIMESLOT);
}

void cb_func(client_data *user_data) //定时器回调函数
{
    //删除非活动连接上的注册事件，并关闭
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
    assert(user_data);
    close(user_data->sockfd);
    std::cout << "close fd: " << user_data->sockfd << std::endl;
}

int main(int argc, char **argv)
{
    int port = 20999;
    int ret = 0;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    int reuse = 1;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    assert(ret != -1);

    ret = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);
    listen(sockfd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    epollfd = epoll_create(5);
    assert(epollfd != -1);

    addfd(epollfd, sockfd);

    //socketpair()函数用于创建一对无名的、相互连接的套接子。
    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd); //可读 可写
    assert(ret != -1);

    setnonblocking(pipefd[1]);
    addfd(epollfd, pipefd[0]);

    //添加信号处理
    addsig(SIGALRM);
    addsig(SIGTERM);

    bool stop_server = false;
    client_data *users = new client_data[FD_LIMIT];
    bool timeout = false;
    alarm(TIMESLOT); //定时

    std::cout << "server start" << std::endl;

    while (!stop_server) {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (number < 0 && errno != EINTR) {
            std::cout << "epoll_wait failed" << std::endl;
            break;
        }

        for (int i = 0; i < number; i++) {
            int listenfd = events[i].data.fd;
            if (listenfd == sockfd) {   //处理新的连接
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);

                int connfd;

                while (((connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength)) == -1) && (errno == EINTR));

                addfd(epollfd, connfd);

                users[connfd].address = client_address;
                users[connfd].sockfd = connfd;

                //创建定时器
                util_timer *timer = new util_timer;
                timer->user_data =  &users[connfd];
                timer->cb_func = cb_func;
                time_t cur = time(NULL);
                timer->expire = cur + 3 * TIMESLOT;

                users[connfd].timer = timer;

                timer_lst.add_timer(timer);
            }
            else if (listenfd == pipefd[0] && events[i].events & EPOLLIN) { //处理信号
                int sig;
                char signals[1024];

                ret = recv(pipefd[0], signals, sizeof(signals), 0);
                if (ret == -1) {
                    continue;
                }
                else if (ret == 0) {
                    continue;
                }
                else {
                    for (int i = 0; i < ret; ++i) {
                        switch (signals[i])
                        {
                            case SIGALRM:
                            {
                                //timeout标记有定时任务需要处理，但不立即处理，因为定时任务优先级不是很高
                                timeout = true;
                                break;
                            }
                            case SIGTERM:
                            {
                                stop_server = true;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
            }
            else if (events[i].events & EPOLLIN) {  //处理收到的客户端数据
                memset(users[listenfd].buf, '\0', BUFFER_SIZE);
                ret = recv(listenfd, users[listenfd].buf, BUFFER_SIZE-1, 0);

                std::cout << "recv: " << users[listenfd].buf << std::endl;

//                printf("get %d bytes of client data: %s from %d\n",
//                       ret, users[listenfd].buf, listenfd);

                util_timer * timer = users[listenfd].timer;

                if (ret < 0) {
                    if (errno != EAGAIN) {  //如果发生读错误，则关闭，并移除对应定时器
                        cb_func(&users[listenfd]);
                        if (timer)
                            timer_lst.del_timer(timer);
                    }
                }
                else if (ret == 0) {
                    //如果对方已关闭，则服务端也关闭，并移除对应定时器
                    cb_func(&users[listenfd]);
                    if (timer)
                        timer_lst.del_timer(timer);
                }
                else {  //如果客户连接上有数据，则调整该连接对应的定时器，以延迟被关闭时间
                    if (timer) {
                        time_t cur = time(NULL);
                        timer->expire = cur + 3 *TIMESLOT;

                        std::cout << "adjust timer once" << std::endl;

                        timer_lst.adjust_timer(timer);
                    }
                }
            }
            else {
                //others
            }
        }

        //最后处理定时事件，因为I/O事件有更高的优先级，
        //但是，这样做将导致定时器任务不能精确
        if (timeout) {
            timer_handler();
            timeout = false;
        }

    }

    close(sockfd);
    close(pipefd[1]);
    close(pipefd[0]);
    delete[] users;

    return 0;
}