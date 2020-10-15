#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cassert>

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        std::cout << "argc <= 2" << std::endl;
        exit(1);
    }

    const char * ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons(port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr *) & addr, sizeof(addr));
    assert(ret != -1);
    ret = listen(listenfd, 20);
    assert(ret != -1);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int connfd = accept(listenfd, (struct sockaddr *) &client_addr, & client_addr_len);

    if(connfd < 0)
    {
        std::cout << "errno = " << errno << std::endl;
        close(listenfd);
    }

    char buf[1024];
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);

    while(true)
    {
        memset(buf, '\0', sizeof(buf));
        FD_SET(connfd, &read_fds);
        FD_SET(connfd, &exception_fds);
        ret = select(connfd + 1, &read_fds, NULL, &exception_fds, NULL);
        if(ret < 0)
        {
            std::cout << "selection failure" << std::endl;
            break;
        }

        if(FD_ISSET(connfd, &read_fds))
        {
            ret = recv(connfd, buf, sizeof(buf) - 1, 0);
            if(ret <= 0)
            {
                break;
            }
            std::cout << "get " << ret << "bytes of normal data = " << buf << std::endl;
        }
        else if(FD_ISSET(connfd, &exception_fds))
        {
            ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
            if(ret <= 0)
            {
                break;
            }
            std::cout << "get " << ret << " bytes of oob data = " << buf << std::endl;
        }
    }

    close(connfd);
    close(listenfd);

    return 0;
}
