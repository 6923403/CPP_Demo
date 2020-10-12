#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    if(argc <= 3)
    {
        std::cout << "argc <= 3" << std::endl;
        exit(-1);
    }

    const char * ip = argv[1];
    int port = atoi(argv[2]);
    const char *file_name = argv[3];

    int filefd = open(file_name, O_RDONLY);
    assert(filefd > 0);

    struct stat stat_buf;
    fstat(filefd, &stat_buf);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr *) &address, sizeof(address));
    assert(ret >= -1);

    ret = listen(sock, 20);
    assert(ret >= -1);

    struct sockaddr_in client;
    socklen_t client_len = sizeof(client);
    int connfd = accept(sock, (struct sockaddr *) &client, &client_len);
    if(connfd < 0)
    {
        std::cout << "errno = " << errno << std::endl;
    }
    else
    {
        sendfile(connfd, filefd, NULL, stat_buf.st_size);
        close(connfd);
    }

    close(sock);

    return 0;
}

