#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    const int BUF_SIZE = 256;
    char * filename = "tr.jpg";

    FILE * fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        printf("Cannot open file. \n");
        exit(-1);
    }

    int sersock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);

    bind(sersock, (struct sockaddr *) &sockAddr, sizeof(sockAddr));
    listen(sersock, 20);

    struct sockaddr_in cl_addr;
    socklen_t cl_addr_size = sizeof(cl_addr);
    int cl_sock = accept(sersock, (struct sockaddr *) &cl_addr, &cl_addr_size);

    char buffer[BUF_SIZE] = {0};
    int nCount;

    while((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0)
    {
        write(cl_sock, buffer, BUF_SIZE);
    }

    shutdown(cl_sock, SHUT_RD);
    close(cl_sock);
    close(sersock);

    return 0;
}
