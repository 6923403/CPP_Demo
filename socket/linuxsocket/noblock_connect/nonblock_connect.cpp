#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <cerrno>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

/*
 * 运行报错 没找到问题
 */

const int BUFFER_SIZE = 1023;

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

int unblock_connect(const char *ip, int port, int time)
{
    int ret = 0;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int fdopt = setnonblocking(sockfd);
    ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));

    if(ret == 0)
    {
        std::cout << "connect with server immediately" << std::endl;
        fcntl(sockfd, F_SETFL, fdopt);
        return sockfd;
    }
    else if(errno != EINPROGRESS)
    {
        std::cout << "unblock connect not support " << std::endl;
        exit(0);
    }

    fd_set readfds;
    fd_set writefds;

    struct timeval timeout;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &writefds);

    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    ret = select(sockfd + 1, NULL, &writefds, NULL, &timeout);
    if(ret <= 0)
    {
        std::cout << "connection time out " << std::endl;
        close(sockfd);
        exit(0);
    }

    if(!FD_ISSET(sockfd, &writefds))
    {
        std::cout << "no events on sockfd found " << std::endl;
        close(sockfd);
        exit(0);
    }

    int error = 0;
    socklen_t len = sizeof(error);

    if(getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
    {
        std::cout << "get socket option failed" << std::endl;
        close(sockfd);
        exit(0);
    }

    if(error != 0)
    {
        std::cout << "connection failed after select with the error: " << error << std::endl;
        exit(0);
    }

    std::cout << "connection ready after select wirh the socket: " << sockfd << std::endl;
    fcntl(sockfd, F_SETFL, fdopt);
    return sockfd;
}

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        std::cout << "argc <= 2" << std::endl;
        exit(1);
    }

    const char * ip = argv[1];
    int port = atoi(argv[2]);

    int sockfd = unblock_connect(ip, port, 10);
    if(sockfd < 0)
    {
        exit(1);
    }

    close(sockfd);
    return 0;
}
