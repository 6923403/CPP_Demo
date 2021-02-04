#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>

const Max_event_num = 1024;
const Buffer_size = 1024;

struct fds
{
    int epollfd;
    int sockfd;
};

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "no port input " << std::endl;
        exit(0);
    }

    int port = atoi(argv[1]);
    
    int ret = 0;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd > 0);
    ret = bind(listenfd, (struct sockaddr* ) &addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(listenfd, 20);
    assert(ret != -1);

    epoll_event events[Max_event_num];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);

    addfd(epollfd, listenfd, false);

    while(true)
    {
        int ret = epoll_wait(epollfd, events, Max_event_num, -1);
        if(ret < 0)
        {
            std::cout << "epoll fdilure " << std::endl;
            break;
        }
        for(int i = 0; i < ret; i++)
        {
            int sockfd = events[i].data.fd;
            if(sockfd == listenfd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);


            }
        }
    }

    return 0;
}
