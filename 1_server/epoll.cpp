#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cassert>
#include <sys/epoll.h>

const int Max_event = 1024;
const int Buf_size = 10;

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option); //设置给arg描述符状态标志
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
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event); //将被监听的描述符添加到epoll句柄或从epoll句柄中删除或者对监听事件进行修改
    setnonblocking(fd);
}

void lt(epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[Buf_size];
    for(int i = 0; i < number; i++)
    {
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd)
        {
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int connfd = accept(listenfd, (struct sockaddr* ) &client_addr, &client_addr_len);
            addfd(epollfd, connfd, false); //禁用et模式
        }
        else if(events[i].events & EPOLLIN)
        {
            //socket读缓存中还有未读出的数据 这段代码就会被触发
            std::cout << "event trigger once " << std::endl;
            memset(buf, '\0', Buf_size);
            int ret = recv(sockfd, buf, Buf_size - 1, 0);
            if(ret < 0)
            {
                close(sockfd);
                continue;
            }
            std::cout << "get " << ret << "bytes of content: " << buf << std::endl;
        }
        else
        {
            std::cout << "something else happend" << std::endl;
        }
    }
}

int main(int argc, char** argv)
{
    std::string ip = "127.0.0.1";
    int port = 12345;
    if(argc > 2)
    {
        ip = argv[1];
        port = atoi(argv[2]);
    }

    int ret = 0;
    struct sockaddr_in address;
    memset(&address, '\0', sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 20);
    assert(ret != -1);

    epoll_event events[Max_event];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    addfd(epollfd, listenfd, true);

    while(true)
    {
        int ret = epoll_wait(epollfd, events, Max_event - 1);
        if(ret < 0)
        {
            std::cout << "epoll error" << std::endl;
            break;
        }
        lt(events, ret, epollfd, listenfd);
    }
    close(listenfd);

    return 0;
}