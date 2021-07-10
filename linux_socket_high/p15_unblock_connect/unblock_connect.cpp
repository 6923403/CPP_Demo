#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <cassert>

int unblock_connect(int port, int time);
int main(int argc, char **argv)
{
    int port = 20999;
    int sockfd = unblock_connect(port, 10);
    if (sockfd < 0)
        return -1;

    std::cout << "send" << std::endl;
    send(sockfd, "123abc", 6, 0 );

    shutdown(sockfd, SHUT_WR);		//关闭sockfd的写功能，此选项将不允许sockfd进行写操作

    std::cout <<  "send data out" << std::endl;
    ssize_t ret = send( sockfd, "abc", 3, 0 );
    if (ret == -1) {
        std::cout << "send failed" << std::endl;
    }

    return 0;
}

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

int unblock_connect(int port, int time)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd != -1);
    int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    int ret = bind(listenfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(listenfd, time);
    assert(ret != -1);

    int fdopt = setnonblocking(listenfd);

    ret = connect(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == 0)
    {
        std::cout << "unblock_connect not support" << std::endl;
        return -1;
    }

    fd_set readfds;
    fd_set writefds;
    struct timeval timeout;
    FD_ZERO(&readfds);
    FD_SET(listenfd, &readfds);

    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    ret = select(listenfd + 1, NULL, &writefds, NULL, &timeout);
    if(ret <= 0)
    {
        std::cout << "connection time out" << std::endl;
        close(listenfd);
        return -1;
    }

    if (!FD_ISSET(listenfd, &writefds)) {
        std::cout << "no events on sockfd found" << std::endl;
        close(listenfd);
        return -1;
    }

    int error = 0;
    socklen_t length = sizeof(error);

    //得到error的值,如果为零,则connect成功.
    if (getsockopt(listenfd, SOL_SOCKET, SO_ERROR, &error, &length) < 0) {
        std::cout << "get socket option failed" << std::endl;
        close(listenfd);
        return -1;
    }

    if (error != 0) {
        std::cout << "connection failed after select with the error: " <<  error << std::endl;
        close(listenfd);
        return -1;
    }

    fcntl(listenfd, F_SETFL, fdopt);

    return listenfd;
}
