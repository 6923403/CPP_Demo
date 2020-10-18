#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <netinet/in.h>

int timeout_connect(const char * ip, int port, int time)
{
    int ret = 0;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &addr.sin_addr);
    addr.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    struct timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    socklen_t len = sizeof(timeout);
    ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
    if(ret == 1)
    {
        if(errno == EINPROGRESS)
        {
            std::cout << "connecting timeout" << std::endl;
            exit(1);
        }
    }

    return sockfd;
}

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        std::cout << "arfc <= 2" << std::endl;
        exit(1);
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int sockfd = timeout_connect(ip, port, 10);
    if(sockfd < 0)
    {
        return 1;
    }


    return 0;
}
