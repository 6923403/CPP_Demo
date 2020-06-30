#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    listen(serv_sock, 20);

    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    char buffer[100] = {0};

    while(true)
    {
        int client_sock = accept(serv_sock, (struct sockaddr *) &client_addr, &client_addr_size);
        int strlen = read(client_sock, buffer, sizeof(buffer) - 1);
        write(client_sock, buffer, sizeof(buffer));

        memset(buffer, 0, sizeof(buffer) - 1);
        close(client_sock);
    }

    close(serv_sock);

    return 0;
}
