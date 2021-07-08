#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

const int MAX_EVENT_NUMBER = 1024;
const int BUFFER_SIZE = 10;

int setnonblocking(int fd);
void addfd(int epollfd, int fd, bool enable_et);
void lt(epoll_event *events, int number, int epollfd, int listenfd);
void et(epoll_event *events, int number, int epollfd, int listenfd);

int main(int argc, char **argv)
{
    int port = 20999;

    struct sockaddr_in addr;
    memset(addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd != -1);

    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    int ret = bind(listenfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);
    ret = listen(listenfd, 10);
    assert(ret != -1);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd > 0);

    addfd(epollfd, sockfd, true);
    while (true) {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0) {
            std::cout << "epoll failed: " <<  strerror(errno)) << std::endl;
            break;
        }

        //lt(events, ret, epollfd, sockfd);		//LT模式
        et(events, ret, epollfd, sockfd);		//ET模式
    }

    return 0;
}

//设置非阻塞文件描述符
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

//将描述符fd的EPOLLIN注册到epollfd提示的epoll内核事件中，参数enable_et指定是否启用ET模式
void addfd(int epollfd, int fd, bool enable_et)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;

    if (enable_et) {
        event.events |= EPOLLET;
    }

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);

    setnonblocking(fd);
}

//LT模式
void lt(epoll_event *events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];

    for (int i = 0; i < number; i++) {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd) {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof(client_address);

            int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
            addfd(epollfd, connfd, false);
        }
        else if (events[i].events & EPOLLIN) {		//只要socket读缓存中还有未读出的数据，就会被触发
            std::cout << "event trigger once" << std::endl;
            memset(buf, '\0', BUFFER_SIZE);

            int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
            if (ret <= 0) {
                close(sockfd);
                continue;
            }

            std::cout << "get: " << ret << " bytes of content: " << buf << std::endl;
        }
        else {
            std::cout << "something else happened" << std::endl;
        }
    }
}

//ET模式
void et(epoll_event *events, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];

    for (int i = 0; i < number; i++) {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd) {
            struct sockaddr_in client_address;
            socklen_t client_addrlength = sizeof(client_address);

            int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
            addfd(epollfd, connfd, true);
        }
        else if (events[i].events & EPOLLIN) {
            std::cout << "event trigger once" << std::endl;
            int ret = 0;

            //因为ET模式不会重复触发，所以我们要循环读取所有数据
            while (1) {
                memset(buf, '\0', BUFFER_SIZE);

                ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
                if (ret < 0) {
                    //对于非阻塞I/O，下面的条件成立时表示数据已全部读取完毕
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        std::cout << "read later!" << std::endl;
                        break;
                    }

                    close(sockfd);
                    break;
                }
                else if (ret == 0) {
                    close(sockfd);
                }
                else {
                    std::cout << "get " ret << " bytes of content: " << buf << std::endl;
                }
            }
        }
        else {
            std::cout << "something else happened" << std::endl;
        }
    }

}