#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/types.h>
#include <cassert>

int connect_timeout(int port, int time)
{
    int ret = 0;
    int error;
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    //超时时间
    struct timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    socklen_t len = sizeof(timeout);
    ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
    assert(ret != -1);

    ret = connect(sockfd, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);

    char buffer[1024];
    memset(buffer, '\0', 1024);
    ret = recv(sockfd, buffer, 1024 - 1, 0);
    std::cout << "recv: " << buffer << std::endl;

    return sockfd;
}

int main(int argc, char **argv)
{
    int port = 20999;
    int sockfd = connect_timeout(port, 10);
    if(sockfd < 0)
    {
        return 1;
    }

    return 0;
}