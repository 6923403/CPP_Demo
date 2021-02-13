#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <signal.h>
#include <cerrno>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>

#include "timer_list.h"

const int FD_LIMIT = 65535;
const int MAX_EVENT_NUM = 1024;
const int TIMESLOT = 5;

static int pipefd[2];
static sore_timer_lst timer_lst;
static int epollfd = 0;

void setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void add(int epollfd, fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

void addsig(int sig)
{
    struct sigaction sa;
    bzero(&sa, sizeof(sa));

    sa.handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sia, NULL) != -1);
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "input ip/port " << std::endl;
        exit(0);
    }

    const int port = atoi(argv[1]);

    int sockfd = 0;
    int ret = 0;

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    ret = bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    assert(ret != -1);

    ret = listen(sockfd, 20);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUM];
    int epollfd = epoll_create(8);
    assert(epollfd != -1);
    addfd(epollfd, sockfd);

    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret != -1);
    setnonblocking(pipefd[1]);
    addfd(epollfd, pipefd[0]);

    addsig(SIGALRM);
    addsig(SIGTERM);

    client_data* users = new client_data[FD_LIMIT];
    bool stop_server = false;
    bool timeout = false;
    alarm(TIMESLOT);

    while(!stop_server) {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUM - 1);

        if ((number < 0) && (errno != EINTR))
        {
            std::cout << "epoll failure" << std::endl;
            exit(0);
        }

        for(int i = 0; i < number; i++)
        {
            int sockfd = events[i].data.fd;

            if(sockfd == epollfd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int connfd = accept(listenfd, (struct sockaddr*) &client_addr, &client_addr_len);
                addfd(epollfd, connfd);

                users[connfd].addr = client_addr;
                users[connfd].sockfd = connfd;

                util_timer* timer = new util_timer;
                timer->user_data = &users[connfd];
                timer->cb_func = cb_func;
                time_t cur = time(NULL);
                timer->expire = cur + 3 * TIMESLOT;
                users[connfd].timer = timer;
                timer_lst.addTimer(timer);
            }
            else if(sockfd == pipefd[0]) && (events[i].events & EPOLLIN)
            {

            }
        }

    }

    return 0;
}