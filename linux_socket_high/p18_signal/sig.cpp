#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <cassert>
#include <sys/epoll.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>

const int MAX_EVENT_SIZE = 1024;
static int pipefd[2];

int setnonblocking(int fd)
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
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
}

void sig_handler(int sig)
{
    int save_errno = errno;
    int msg = sig;
    send(pipefd[1], (char*)&msg, 1, 0);		//将信号写入管道，以通知主循环
    errno = save_errno;
}

void addsig(int sig)
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;

    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char **argv)
{
    int port = 20999;
    if(argc > 1)
    {
        port = atoi(argv[1]);
    }

    int ret = 0;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    ret = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(sockfd, 10);
    assert(ret != -1);

    std::cout << "server bind and listen success" << std::endl;

    epoll_event events[MAX_EVENT_SIZE];
    int epollfd = epoll_create(5);

    addfd(epollfd, sockfd);

    //使用socketpair创建管道，注册pipefd[0]上的可读事件
    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret != -1);
    setnonblocking(pipefd[1]);
    addfd(epollfd, pipefd[0]);

    //设置信号处理
    addsig(SIGHUP);
    addsig(SIGCHLD);
    addsig(SIGTERM);
    addsig(SIGINT);

    bool stop_server = false;
    while(!stop_server)
    {
        int num = epoll_wait(epollfd, events, MAX_EVENT_SIZE, -1);
        if(num < 0)
        {
            continue;
        }
        for(int i = 0; i < num; i++)
        {
            int listenfd = events[i].data.fd;
            if(listenfd == sockfd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);

                int connfd = -1;
                connfd = accept(listenfd, (struct sockaddr*) &client_addr, &client_addr_len);

                addfd(epollfd, connfd);
            }
            else if(listenfd == pipefd[0] && events[i].events & EPOLLIN)
            {
                char signals[1024];
                ret = recv(pipefd[0], signals, sizeof(signals), 0);
                if (ret == -1)
                    continue;
                else if (ret == 0)
                    continue;
                else
                {
                    //每个信号值占1字节，所以按字节来逐个接收信号
                    for(int i = 0; i < ret; i++)
                    {
                        switch(signals[i])
                        {
                            case SIGCHLD:
                            {
                                std::cout << "recv SIGCHLD" << std::endl;
                                continue;
                                break;
                            }
                            case SIGHUP:
                            {
                                std::cout << "recv SIGHUP" << std::endl;
                                continue;
                                break;
                            }
                            case SIGTERM:
                            {
                                std::cout << "recv SIGTERM, close server" << std::endl;
                                stop_server = true;
                                break;
                            }
                            case SIGINT:
                            {
                                std::cout << "recv SIGINT, close server" << std::endl;
                                stop_server = true;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }
    printf("close fds\n");
    close(sockfd);
    close(pipefd[1]);
    close(pipefd[0]);

    return 0;
}