#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(20999);
    addr.sin_addr.s_addr = inet_addr("192.168.1.17");

    const int buf_size = 10240;
    char buf[buf_size] = {0};
    memset(buf, 0, buf_size);

    int ret = connect(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret == 0);

    while(recv(sockfd, buf, buf_size, 0) > 0){};

    std::cout << buf << std::endl;

    return 0;
}