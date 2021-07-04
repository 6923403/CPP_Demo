#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cassert>

int main(int argc, char **argv)
{
    int port = atoi(argv[1]);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr  = htonl(INADDR_ANY);
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    if (connfd < 0) {
        printf("error: %s\n", strerror(errno));
    }
    else {
        close(STDOUT_FILENO); //关闭标准输出
        dup(connfd);          //重定向1到connfd，这样服务器的标准输出内容会直接发送到客户端socket，这就是CGI的基本原理

        printf("abc. close stdout_fileno test... dup to client\n"); //printf会直接输出会发送到客户端

        close(connfd);
    }

    close(sock);

    return 0;
}