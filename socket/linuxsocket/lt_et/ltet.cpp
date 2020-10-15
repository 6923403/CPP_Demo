#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cassert>
#include <cstring>
#include <fcntl.h>
#include <cstdlib>
#include <pthread.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

const int MAX_EVENT_NUMBER = 1024;
const int BUFFER_SIZE = 10;

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

void addfd(int epollfd, int fd, bool enable_et)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if(enable_et)
    {
        event.events |= EPOLLET;
    }

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

void lt(epoll_event * events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for(int i = 0; i < number; i++)
    {
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd)
        {
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int connfd = accept(listenfd, (struct sockaddr *) &client_addr, &client_addr_len);

            addfd(epollfd, connfd, false);
        }
        else if(events[i].events & EPOLLIN)
        {
            std::cout << "event trigger once" << std::endl;
            memset(buf, '\0', BUFFER_SIZE);
            int ret = recv(sockfd, buf, BUFFER_SIZE -1, 0);
            if(ret <= 0)
            {
                close(sockfd);
                continue;
            }
            std::cout << "get " << ret << " bytes of content: " << buf << std::endl;
        }
        else
        {
            std::cout << "Something else happened" << std::endl;
        }
    }
}

void et(epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for(int i = 0; i < number; i++)
    {
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd)
        {
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);

            int connfd = accept(listenfd, (struct sockaddr*) &client_addr, &client_addr_len);

            addfd(epollfd, connfd, true);
        }
        else if(events[i].events & EPOLLIN)
        {
            std::cout << "event trigger once " << std::endl;
            while(true)
            {
                memset(buf, '\0', BUFFER_SIZE);
                int ret = recv(sockfd, buf, BUFFER_SIZE - 1, 0);

                if(ret < 0)
                {
                    if((errno == EAGAIN) || (errno == EWOULDBLOCK))
                    {
                        std::cout << "Read lager" << std::endl;
                        break;
                    }
                    close(sockfd);
                    break;
                }
                else if(ret == 0)
                {
                    close(sockfd);
                }
                else
                {
                    std::cout << "get " << ret << " bytes of content " << buf << std::endl;
                }
            }
        }
        else
        {
            std::cout << "Something else happened " << std::endl;
        }
    }
}

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        std::cout << "argc <= 2" << std::endl;
        exit(0);
    }

    const char * ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr *) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);

    addfd(epollfd, listenfd, true);

    while(true)
    {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);

        if(ret < 0)
        {
            std::cout << "epoll failure" << std::endl;
            break;
        }

        lt(events, ret, epollfd, listenfd);
        //et(events, ret, epollfd, listenfd);
    }

    close(listenfd);

    return 0;
}
