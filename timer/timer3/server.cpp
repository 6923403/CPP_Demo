#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //write close
#include <arpa/inet.h> //inet_addr
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in s_addr;
    memset(&s_addr, 0, sizeof(s_addr));

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_port = htons(20999);

    bind(sockfd, (struct sockaddr *) &s_addr, sizeof(s_addr));

    listen(sockfd, 20);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_len = sizeof(clnt_addr);
    sleep(11);
    int clntfd = accept(sockfd, (struct sockaddr*) &clnt_addr, &clnt_addr_len);

    char str[] = "Hello, World";

    write(clntfd, str, sizeof(str));

    close(clntfd);
    close(sockfd);

    return 0;
}