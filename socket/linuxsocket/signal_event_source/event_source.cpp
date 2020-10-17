#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cerrno>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <netinet/in.h>

const int MAX_EVENT_NUMBER = 1024;
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
    setnonblocking(fd);
}

void sig_handler(int sig)
{
    int save_errno = errno;
    int msg = sig;
    send(pipefd[1], (char *) &msg, 1, 0);
    errno = save_errno;
}

void addsig(int sig)
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags != SA_RESTART;
    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        std::cout << "argc <= 2" << std::endl;
        exit(1);
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr*) &addr, sizeof(addr));
    if(ret == -1)
    {
        std::cout << "bind errno:" << errno << std::endl;
        exit(1);
    }

    ret = listen(listenfd, 10);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    addfd(epollfd, listenfd);

    ret = socketpair(AF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret != -1);
    setnonblocking(pipefd[1]);
    addfd(epollfd, pipefd[0]);

    addsig(SIGHUP);
    addsig(SIGCHLD);
    addsig(SIGINT);

    bool stop_server = false;

    while(!stop_server)
    {
        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if((number < 0) && (errno != EINTR))
        {
            std::cout << "epoll failure" << std::endl;
            break;
        }

        for(int i = 0; i < number; i++)
        {
            int sockfd = events[i].data.fd;

            if(sockfd == listenfd)
            {
                struct sockaddr_in client_address;
                socklen_t client_address_len = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr*) &client_address, &client_address_len);
                addfd(epollfd, connfd);
            }
            else if((sockfd == pipefd[0]) && (events[i].events & EPOLLIN))
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
                    for(int i = 0; i < ret; ++i)
                    {
                        switch(signals[i])
                        {
                            case SIGCHLD:
                            case SIGHUP:
                                continue;
                            case SIGTERM:
                            case SIGINT:
                                stop_server = true;
                        }

                    }
                }
            }
        }
    }

    std::cout << "close fds" << std::endl;

    close(listenfd);
    close(pipefd[1]);
    close(pipefd[0]);

    return 0;
}
