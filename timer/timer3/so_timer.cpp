#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cassert>
#include <cstdlib>
#include <errno.h>
#include <time.h>

int timeout_connect(const char *ip, int port, int time)
{
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &s_addr.sin_addr);
    s_addr.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    struct timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;
    socklen_t addr_len = sizeof(s_addr);
    int ret = 0;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, addr_len);
    assert(ret != -1);

    ret = connect(sockfd, (struct sockaddr*) &s_addr, sizeof(s_addr));
    if(ret == -1)
    {
        if(errno == EINPROGRESS)
        {
            std::cout << "connecting timeout" << std::endl;
            return -1;
        }
        std::cout << "errno" << std::endl;
        return -1;
    }

    return sockfd;
}

int main(int argc, char **argv)
{
    int port = 20999;
    const char *ip = "127.0.0.1";

    int sockfd = timeout_connect(ip, port, 10);

    std::cout << sockfd << std::endl;
    return 0;
}