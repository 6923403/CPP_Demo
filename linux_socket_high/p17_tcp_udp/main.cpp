#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <cassert>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

const int MAX_EVENT_NUMBER = 1024;
const int TCP_BUFFER_SIZE = 512;
const int UDP_BUFFER_SIZE = 1024;

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
    event.events = EPOLLIN;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);

    setnonblocking(fd);
}

int main(int argc, char **argv)
{
    int port = 20999;
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "tcp start" << std::endl;
    assert(sockfd != -1);

    int reuse = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    assert(ret != -1);

    if((bind(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) || (listen(sockfd, 5) == -1)) {
        exit(0);
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    int udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    std::cout << "udp start" << std::endl;
    assert(udpfd != -1);

    ret = bind(udpfd, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);

    addfd(epollfd, sockfd);
    addfd(epollfd, udpfd);

    while(true)
    {
        int n = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        assert(n >= 0);
        for(int i = 0; i < n; i++)
        {
            int listenfd = events[i].data.fd;
            if(listenfd == sockfd)
            {
                struct sockaddr_in client_address;
                socklen_t client_addr_len = sizeof(client_address);

                int connfd;
                while ( ((connfd = accept(sockfd, (struct sockaddr*)&client_address, &client_addr_len)) == -1) &&
                        (connfd == EINTR));

                addfd(epollfd, connfd);
            }
            else if (listenfd == udpfd) {
                char buf[UDP_BUFFER_SIZE];
                memset(buf, '\0', UDP_BUFFER_SIZE);

                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);

                ret = recvfrom(udpfd, buf, UDP_BUFFER_SIZE-1, 0, (struct sockaddr*)&client_address, &client_addrlength);
                if (ret > 0)
                {
                    sendto(udpfd, buf, UDP_BUFFER_SIZE-1, 0, (struct sockaddr*)&client_address, client_addrlength);
                }
            }
            else if (events[i].events & EPOLLIN) {
                char buf[TCP_BUFFER_SIZE];
                while(true) {
                    memset(buf, '\0', TCP_BUFFER_SIZE);
                    ret = recv(listenfd, buf, TCP_BUFFER_SIZE, 0);
                    if (ret < 0)
                    {
                        close(listenfd);
                        break;
                    }
                    else if (ret == 0)
                        close(listenfd);
                    else
                        std::cout << "recv: " << buf << std::endl;
                        send(listenfd, buf, ret, 0);
                }
            }
            else
            {
                std::cout << "something else happened" << std::endl;
            }
        }
    }

    close(sockfd);

    return 0;
}