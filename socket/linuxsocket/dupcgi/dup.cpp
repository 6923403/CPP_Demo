#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstdlib>
#include <cassert>
#include <cstring>

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        std::cout << "usage: " << basename(argv[0]) << " ipaddr port_number" << std::endl;

        exit(1);
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr *) &address, sizeof(address));
    assert(sock >= -1);

    ret = listen(sock, 20);
    assert(ret >= -1);

    struct sockaddr_in clnt;
    socklen_t clnt_len = sizeof(clnt);
    int connfd = accept(sock, (struct sockaddr *) &clnt, &clnt_len);
    if(connfd < 0)
    {
        std::cout << "errno is: " << errno << std::endl;
    }
    else
    {
        close(STDOUT_FILENO);
        dup(connfd);
        std::cout << "ABCD " << std::endl;
        close(connfd);
    }

    close(sock);

    return 0;
}
