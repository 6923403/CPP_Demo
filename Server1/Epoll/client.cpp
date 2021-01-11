#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    int port = 15009;
    if(argc > 1)
    {
        port = atoi(argv[1]);
    }
    int connfd;
    struct sockaddr_in serv_addr;
    char buf[1024];

    connfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = port;
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);

    connect(connfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while(fgets(buf, 1024, stdin) != NULL){
        write(connfd, buf, strlen(buf));
    }

    close(connfd);
    return 0;

    return 0;
}
