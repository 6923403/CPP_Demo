#include <iostream>
#include <cassert>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

const int BUFFER_SIZE = 512;

int main(int argc, char **argv)
{
    if(argc <= 2)
    {
        cout << "ip/port error!" << endl;
        exit(0);
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    cout << "ip = " << argv[1] << "  port = " << argv[2] << endl;

    struct sockaddr_in clnt_addr;
    bzero(&clnt_addr, sizeof(clnt_addr));
    clnt_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &clnt_addr.sin_addr);
    clnt_addr.sin_addr.s_addr = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int sendbuf = atoi(argv[3]);
    int len = sizeof(sendbuf);

    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t *) &len);
    cout << "send buffer size = " << sendbuf << endl;

    if(connect(sock, (struct sockaddr *) &clnt_addr, sizeof(clnt_addr)) != -1)
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, 'a', BUFFER_SIZE);
        /*
         * ssize_t send(int sockfd, const void *buf, size_t len, int flags)
         */
        send(sock, buffer, BUFFER_SIZE, 0);
    }

    close(sock);

    return 0;
}
