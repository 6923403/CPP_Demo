#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

int main(int argc, char **argv)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(12521);

    connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    char buf[40];
    read(sock, buf, sizeof(buf) - 1);

    std::cout << "BUF = " << buf << std::endl;

    close(sock);

    return 0;
}
