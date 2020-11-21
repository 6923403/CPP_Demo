#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr)); //bzero
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(12345);

    connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    char buffer[48];
    read(sock, buffer, sizeof(buffer) - 1);
    std::cout << "Message form server: " << buffer << std::endl;

    close(sock);

    return 0;
}
