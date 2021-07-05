#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cassert>
//没玩明白

int main(int argc, char **argv)
{
    int port = 20999;
    std::string ip = "127.0.0.1";
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    assert(ret != -1);
    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);

    int connfd = accept(sockfd, (struct sockaddr*)&client, &client_addrlength);
    if (connfd < 0)
    {
        printf("errno is: %s\n", strerror(errno));
    }
    else
    {
        int pipefd[2];
        ret = pipe(pipefd);
        assert(ret != -1);

        ret = splice(connfd, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        assert(ret != -1);

        //将管道的输出定向到connfd上
        ret = splice(pipefd[0], NULL, connfd, NULL,
                     32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        assert(ret != -1);

        close(connfd);
    }

    close(sockfd);

    return 0;
}