#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>


int main(int argc, char **argv)
{
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(12521);

    bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    listen(serv_sock, 20);

    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);

    char str[] = "AAAAA";
    write(clnt_sock, str, sizeof(str));

    close(clnt_sock);
    close(serv_sock);

    return 0;
}
