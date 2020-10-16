#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cassert>
#include <cerrno>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

const int MAX_EVENT_NUMBER = 1024;
const int BUFFER_SIZE = 1024;

struct fds
{
    int epollfd;
    int sockfd;
};

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void addfd(int epollfd, int fd, bool onehost)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if(onehost)
    {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

void reset_oneshot(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

void * worker(void * arg)
{
    int sockfd = ((fds *) arg)->sockfd;
    int epollfd = ((fds *) arg)->epollfd;
    std::cout << "start new thread to receive data on fd: " << sockfd << std::endl;
    char buf[BUFFER_SIZE];
    memset(buf, '\0', BUFFER_SIZE);

    while(true)
    {
        int ret = recv(sockfd, buf, BUFFER_SIZE - 1, 0);
        if(ret == 0)
        {
            close(sockfd);
            std::cout << "foreiner closed the connection" << std::endl;
            break;
        }
        else if(ret < 0)
        {
            if(errno == EAGAIN)
            {
                reset_oneshot(epollfd, sockfd);
                std::cout << "read later" << std::endl;
                break;
            }
        }
        else
        {
            std::cout << "get content: " << buf << std::endl;
            sleep(3);
        }

        std::cout << "end thread receiving data on fd: " << sockfd << std::endl;
    }
}

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        std::cout << "argc <= 2" << std::endl;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr *) &addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);

    addfd(epollfd, listenfd, false);

    while(true)
    {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if(ret < 0)
        {
            std::cout << "epoll failure " << std::endl;
            break;
        }

        for(int i = 0; i < ret; i++)
        {
            int sockfd = events[i].data.fd;
            if(sockfd == listenfd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int connfd = accept(listenfd, (struct sockaddr *) &client_addr, &client_addr_len);
                addfd(epollfd, connfd, true);
            }
            else if(events[i].events & EPOLLIN)
            {
                pthread_t thread;
                fds fds_for_new_worker;
                fds_for_new_worker.epollfd = epollfd;
                fds_for_new_worker.sockfd = sockfd;
                pthread_create(&thread, NULL, worker, (void *)&fds_for_new_worker);
            }
            else
            {
                std::cout << "something else happened " << std::endl;
            }
        }
    }

    close(listenfd);

    return 0;
}
