#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <errno.h>
#include <cstring>
#include <cassert>

using namespace std;

const int BUFFER_SIZE = 1024;

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        cout << "ip/port error!" << endl;
        exit(0);
    }

    const char * ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int recvbuf = atoi(argv[3]);
    int len = sizeof(recvbuf);

    cout << "setsockopt" << endl;
    setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t *) &len);

    cout << "buffer size = " << recvbuf << endl;

    int ret = bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlen;
    int connfd = accept(sock, (struct sockaddr *) &client, &client_addrlen);
    if(connfd < 0)
    {
        cout << "errno is: " << errno << endl;
    }
    else
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        while(recv(connfd, buffer, BUFFER_SIZE - 1, 0) > 0) {}
        close(connfd);
    }

    close(sock);

    return 0;
}
