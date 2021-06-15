#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#include "lst_timer.h"

const int FD_LIMIT = 65535;
const int MAX_EVENT_NUM = 1024;
const int TIMESLOT = 5;
static int pipefd[2];
static lst_timer timer_lst;
static int epollfd = 0;

void setnoblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void addfd(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &evnt);
    setnoblocking(fd);
}

void addsig(int sig)
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sighandler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, nullptr) != -1);
}

void timer_handler()
{
    timer_lst.tick();
    alarm(TIMESLOT);
}

void cb_func(client_data *user_data)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
    assert(user_data);
    close(user_data->sockfd);
    std::cout << "close fd = " << user_data->sockfd << std::endl;
}

int main(int argc, char **argv)
{
    int port = 20999;
    int ret = 0;
    struct sockaddr_in address;
    memset(&address, 0, sizeof(s_addr));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int ret = 0;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    ret = bind(sockfd, (struct sockaddr_in*) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUM];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    addfd(epollfd, sockfd);

    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret != -1);
    setnoblocking(pipefd[1]);
    addfd(epollfd, pipefd[0]);

    addsig(SIGALRM);
    addsig(SIGTERM);
    bool stop_server = false;

    client_data *users = new client_data[FD_LIMIT];
    bool timeout = false;
    alarm(TIMESLOT);

    while(!stop_server)
    {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUM - 1);
        if((number < 0) && (errno != EINTR))
        {
            std::cout << "epoll failure" << std::endl;
            break;
        }

        for(int i = 0; i < number; i++)
        {
            int m_sockfd = events[i].data.fd;
            if(m_sockfd == sockfd)
            {
                /*
                 * 新用户请求
                 */
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int connfd = accept(sockfd, (struct sockaddr*) &client_addr, &client_addr_len);
                addfd(epollfd, connfd);
                users[connfd].address = client_addr;
                users[connfd].sockfd = connfd;

                util_timer *timer = new util_timer;
                timer->user_data = &users[connfd];
                timer->cb_func = cb_func;
                time_t cur = time(NULL);
                timer->expire = cur + 3 * TIMESLOT;
                users[connfd].timer = timer;
                timer_lst.add_timer(timer);
            }
            /*
             * 处理信号
             */
            else if((m_sockfd == pipefd[0]) && (events.events & EPOLLIN))
            {
                int sig;
                char signals[1024];
                ret = recv(pipefd[0], signals, sizeof(signals), 0);
                if(ret == -1)
                {
                    continue;
                }
                else if(ret == 0)
                {
                    continue;
                }
                else
                {
                    for(int i = 0; i < ret; i++)
                    {
                        switch (signals[i])
                        {
                            case SIGALRM:
                                timeout = true;
                                break;
                            case SIGTERM:
                                stop_server = true;
                        }
                    }
                }
            }
            else if(events[i].events & EPOLLIN) {
                memset(users[m_sockfd].buf, '\0', BUF_SIZE);
                ret = recv(m_sockfd, users[m_sockfd].buf, BUF_SIZE - 1, 0);
                std::cout << "get " << ret << " bytes if client data " << users[m_sockfd].buf << " from " << m_sockfd
                          << std::endl;

                util_timer *timer = users[m_sockfd].timer;
                if (ret < 0) {
                    //发生读错误 关闭连接 移除定时器
                    if (errno != EAGAIN) {
                        cb_func(&users[sockfd]);
                        if (timer) {
                            timer_lst.del_timer(timer);
                        }
                    }
                } else if (ret == 0) {
                    //关闭连接 移除定时器
                    cb_func(&users[sockfd]);
                    if (timer) {
                        timer_lst.del_timer(timer);
                    }
                } else {
                    if (timer) {
                        time_t cur = time(nullptr);
                        timer->expire = cur + 3 + TIMESLOT;
                        std::cout << "addjust_timer once " << std::endl;
                        timer_lst.adjust_tiimer(timer);
                    }
                }
            }
            else
            {
                continue;
            }
        }
        if(timeout)
        {
            tiimer_handler();
            timeout = false;
        }
    }

    return 0;
}