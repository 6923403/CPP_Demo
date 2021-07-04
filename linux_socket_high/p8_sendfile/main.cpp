#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>

int main()
{
    int port = 20999;
    int filefd = open("1.txt", O_RDONLY);
    assert(filefd > 0);

    struct stat stat_buf;
    fstat(filefd, &stat_buf);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    int ret = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(sockfd, 10);
    assert(ret != -1);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr_len);

    int connfd = accept(sockfd, (struct sockaddr*) &client_addr_len, &client_addr_len);
    if(connfd < 0)
    {
        return 0;
    }

    sendfile(connfd, filefd, NULL, stat_buf.st_size);
    close(connfd);
    close(sockfd);

    return 0;
}