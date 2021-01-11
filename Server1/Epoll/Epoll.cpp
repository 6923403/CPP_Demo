/*
 * epoll_create()系统调用。此调用返回一个句柄，之后所有的使用都依靠这个句柄来标识
 * epoll_ctl()系统调用。通过此调用向epoll对象中添加、删除、修改感兴趣的事件，返回0标识成功，返回-1表示失败
 * epoll_wait()系统调用。通过此调用收集收集在epoll监控中已经发生的事件。
 */

#include <iostream>
#include <cstring>
#include <cassert>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>

const int max_events = 500;
const int buffer_size = 10;

int setnonblocking(int fd)
{
    int old_opt = fcntl(fd, F_GETFD);
    int new_opt = old_opt | O_NONBLOCK;
    fcntl(fd, F_SETFD, new_opt);

    return old_opt;
}//将文件描述符设置为非阻塞的

int test_Listen_socket(int m_epollfd, int port)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    return listenfd;
    /*
     * https://www.cnblogs.com/xuyh/p/3273082.html fcntl
     * fcntl(listenfd, F_SETFL, O_NONBLOCK);
     * std::cout << "server listen fd = " << listenfd << std::endl;
     * Event_set(&events[max_events], listenfd, )
     * //EventSet(&g_Events[MAX_EVENTS], listenFd, AcceptConn, &g_Events[MAX_EVENTS]);
     */
}

void addfd(int epollfd, int fd, int enable_et)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if(enable_et)
    {
        event.events |= EPOLLET;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
}

int Listen_socket(int m_epollfd, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = port;
    serveraddr.sin_addr.s_addr = htons(INADDR_ANY);

    bind(sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    listen(sock, 128);

    return sock;
}

void lt(struct epoll_event *events, int num, int epollfd, int listenfd)
{
    char buf[buffer_size];
    for(int i = 0; i < num; i++){
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd){
            struct sockaddr_in clientaddr;
            socklen_t clilen = sizeof(clientaddr);
            int connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clilen);
            addfd(epollfd, connfd, 0);//对connfd使用默认的lt模式
        }else if(events[i].events & EPOLLIN){//只要socket读缓存中还有未读的数据，这段代码就会触发
            printf("event trigger once\n");
            memset(buf, '\0', buffer_size);
            int ret = recv(sockfd, buf, buffer_size - 1, 0);
            if(ret <= 0){
                close(sockfd);
                continue;
            }
            printf("get %d bytes of content:%s\n", ret, buf);
        }else{
            printf("something else happened\n");
        }
    }
}

void et(struct epoll_event *event, int num, int epollfd, int listenfd)
{
    char buf[buffer_size];
    for(int i = 0; i < num; i++){
        int sockfd = event[i].data.fd;
        if(sockfd == listenfd){
            struct sockaddr_in clientaddr;
            socklen_t clilen = sizeof(clientaddr);
            int connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clilen);
            addfd(epollfd, connfd, 1);//多connfd开启ET模式
        }else if(event[i].events & EPOLLIN){
            printf("event trigger once\n");
            while(1){//这段代码不会重复触发，所以要循环读取数据
                memset(buf, '\0', buffer_size);
                int ret = recv(sockfd, buf, buffer_size - 1, 0);
                if(ret < 0){
                    if((errno == EAGAIN) || (errno == EWOULDBLOCK)){
                        printf("read later\n");
                        break;
                    }
                    close(sockfd);
                    break;
                }else if(ret == 0){
                    close(sockfd);
                }else{
                    printf("get %d bytes of content:%s\n", ret, buf);
                }
            }
        }else{

            printf("something else happened \n");
        }
    }
}

int main(int argc, char **argv)
{
    int port = 15009;
    if(argc > 1)
    {
        port = atoi(argv[1]);
    }

    epoll_event events[max_events];
    int m_epollfd = epoll_create(5);
    assert(m_epollfd != -1);

    int listenfd = Listen_socket(m_epollfd, port);
    addfd(m_epollfd, listenfd, true);

    while(true)
    {
        int ret = epoll_wait(m_epollfd, events, max_events, -1);
        if(ret < 0)
        {
            std::cout << "epoll failure" << std::endl;
            break;
        }
        lt(events, ret, m_epollfd, listenfd);//lt模式
        //et(events, ret, epollfd, listenfd);//et模式
    }

    close(listenfd);
    return 0;
}
