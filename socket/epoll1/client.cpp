#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "argc < 2 " << std::endl;
        exit(0);
    }
    int port = atoi(argv[1]);
    int connfd;
    struct sockaddr_in client_addr;
    char buf[1024];

    connfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    inet_aton("101", &client_addr.sin_addr);
    client_addr.sin_port = htons(port);

    connect(connfd, (struct sockaddr* ) &client_addr, sizeof(client_addr));

    while(true)
    {
        int ret = send(connfd, buf, sizeof(buf + 1), 0);
        if(ret == 0)
        {
            std::cout << "connect server " << std::endl;
            continue;
        }
        else if(ret < 0)
        {
            std::cout << "error " << std::endl;
            break;
        }
    }
    close(connfd);

    return 0;
}
