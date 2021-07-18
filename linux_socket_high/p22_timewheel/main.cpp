//nonactive_conn.cpp
//关闭非活动连接
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <assert.h>
#include <signal.h>
#include <cassert>

#include "tw_timer.h"

const int FD_LIMIT = 65535;
const int MAX_EVENT_NUMBER = 1024;
const int TIMESLOT = 100;

static int pipefd[2];
static time_wheel client_conn_time_wheel;
static int epollfd = 0;

int setnonblocking(int fd);             //设置非阻塞
int addfd(int epollfd, int fd);         //添加描述符事件

void sig_handler(int sig);              //信号处理函数
void addsig(int sig);                   //添加信号处理函数

void timer_handler();                   //定时器任务
void cb_func(client_data *user_data);   //定时器回调函数


int main(int argc, char *argv[])
{
    int port = 20999;

    int ret = 0;
    int error;

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    int reuse = 1;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    assert(ret != -1);

    if ( (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) || (listen(sockfd, 5) == -1))
    {
        return 0;
    }

    int epollfd = epoll_create(5);
    assert(epollfd != -1);

    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];

    setnonblocking(pipefd[1]);
    addfd(epollfd, pipefd[0]);
    addfd(epollfd, sockfd);

    //添加信号处理
    addsig(SIGALRM);
    addsig(SIGTERM);

    bool stop_server = false;

    client_data *users = new client_data[FD_LIMIT];
    bool timeout = false;

    alarm(1);

    std::cout << "server start" << std::endl;

    while (!stop_server) {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (number < 0 && errno != EINTR) {
            std::cout << "epoll_wait failed" << std::endl;
            break;
        }

        for (int i = 0; i < number; i++) {
            int listenfd = events[i].data.fd;

            if (listenfd == sockfd) {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);

                int connfd;

                while ( ((connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength)) == -1) &&
                        (errno == EINTR));

                addfd(epollfd, connfd);

                users[connfd].address = client_address;
                users[connfd].sockfd = connfd;

                tw_timer *timer = NULL;
                timer = client_conn_time_wheel.add_timer(TIMESLOT);
                if (timer) {
                    timer->user_data = &users[connfd];
                    timer->cb_func = cb_func;
                    users[connfd].timer = timer;
                    std::cout << "client: " << connfd << " add tw_timer successed" << std::endl;
                }
                else {
                    std::cout << "client: " << connfd << " add tw_timer failed" << std::endl;
                }

            }
            else if((listenfd == pipefd[0]) && (events[i].events & EPOLLIN)) {
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
                    for (int i = 0; i < ret; i++) {
                        switch (signals[i]) {
                            case SIGALRM:
                            {
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
            else if (events[i].events & EPOLLIN) {
                memset(users[listenfd].buf, '\0', BUFFER_SIZE);

                ret = recv(listenfd, users[listenfd].buf, BUFFER_SIZE-1, 0);
                std::cout << "get:" << ret << " bytes of client data: "<< users[listenfd].buf << " from:" listenfd << std::endl;

                tw_timer *timer = users[listenfd].timer;

                if (ret < 0) {
                    if (errno != EAGAIN) {
                        cb_func(&users[listenfd]);
                        if (timer)
                            client_conn_time_wheel.del_timer(timer);
                    }
                }
                else if (ret == 0) {
                    cb_func(&users[listenfd]);
                    if (timer)
                        client_conn_time_wheel.del_timer(timer);
                }
                else {
                    if (timer) {
                        std::cout << "conntioned..to do adjuest timer" << std::endl;
                    }
                }
            }
            else {

            }

        }

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


int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

int addfd(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

void sig_handler(int sig)
{
    int save_error = errno;
    int msg = sig;
    send(pipefd[1], (char*)&msg, 1, 0);
    errno = save_error;
}

void addsig(int sig)
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;

    sigfillset(&sa.sa_mask); //将所有信号加入至信号集

    assert(sigaction(sig, &sa, NULL) != -1);
}

void timer_handler()
{
    client_conn_time_wheel.tick();
    alarm(1);
}

void cb_func(client_data *user_data)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
    assert(user_data);
    close(user_data->sockfd);
    std::cout << "close fd: " << user_data->sockfd << std::endl;
}