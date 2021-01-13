#include <iostream>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int port = 16000;
    if(argc > 1)
    {
        port = atoi(argv[1]);
    }

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);

    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(serv_sock != 0);
    int ret = bind(serv_sock, (struct sockaddr* ) &serv_addr, sizeof(serv_addr));
    assert(ret != -1);

    ret = listen(serv_sock, 10);

    int connfd;
    while(true)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        connfd = accept(serv_sock, (struct sockaddr* ) &serv_addr, &client_addr_len);
        if(connfd < 0)
        {
            std::cout << "Faild" << std::endl;
            continue;
        }

        char requests[1024];
        recv(connfd, requests, 1024, 0);

        std::cout << "recv Success \n" << requests << std::endl;
        char buf[1024] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";
        int s = send(connfd, buf, strlen(buf), 0);

        int fd = open("hello.html", O_RDONLY);
        sendfile(connfd, fd, NULL, 2500);
        close(fd);
        close(connfd);
    }

    return 0;
}
