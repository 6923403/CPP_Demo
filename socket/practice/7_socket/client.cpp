#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char** argv)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr("101.132.159.69");
    s_addr.sin_port = htons(20999);

    connect(sockfd, (struct sockaddr*) &s_addr, sizeof(s_addr));
    char buffer[40];
    read(sockfd, buffer, sizeof(buffer)-1);

    std::cout << "server: " << buffer << std::endl;


    close(sockfd);

    return 0;
}