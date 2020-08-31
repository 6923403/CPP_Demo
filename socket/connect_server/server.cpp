#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    int ser_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in ser_addr;
    memset(&ser_addr, 0, sizeof(ser_addr));

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htons(INADDR_ANY);
    ser_addr.sin_port = htons(server_port);
    bind(ser_sock, (struct sockaddr *) &ser_addr, sizeof(ser_addr));

    listen(ser_sock, 20);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    int clnt_sock = accept(ser_sock, (struct sockaddr *) & clnt_addr, &clnt_addr_size);
    char buffer[256];

    //int fd, void *buf, size_t nbytes
    int strlen = read(clnt_sock, buffer, sizeof(buffer) - 1 );
    printf("Client: %s \n", buffer);

    write(clnt_sock, buffer, sizeof(buffer));

    close(clnt_sock);
    close(ser_sock);

    return 0;
}
