#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char** argv)
{
    int sockfd = 0;
    int time = 5;
    int port = 10234;

    if(argc <= 2)
    {
        std::cout << "no ip/port input" << std::endl;
        exit(0);
    }

    const char* ip = argv[1];
    port = atoi(argv[2]);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    int ret = 0;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd > 0);

    struct timeval timeout;
    timeout.tv_sec = time;
    timeout.tv_usec = 0;

    socklen_t time_len = sizeof(timeout);
    //socklen_t serv_addr_len = sizeof(serv_addr);
    ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, time_len); //发送数据超时
    assert(ret != -1);

    ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    if(ret == -1)
    {
        //超时 对应错误号 EINPROGRESS
        if(errno == EINPROGRESS)
        {
            std::cout << "connecting timeout" << std::endl;
            exit(0);
        }
    }

    close(sockfd);

    return 0;
}