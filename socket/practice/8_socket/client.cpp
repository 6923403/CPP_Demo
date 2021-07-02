#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <assert.h>
#include <cstring>

int main(int argc, char **argv)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(sockaddr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(20111);

    struct sockaddr_in saddr;
    socklen_t saddr_len = sizeof(saddr);
    char buf[2048] = {0};
    char sendbuf[2048] = {0};
    //string s="hello,world!";
    //strcpy(n,s.c_str());
    while(true)
    {
        memset(buf, 0, sizeof(buf));
        memset(sendbuf, 0, sizeof(sendbuf));
        int s_socketfd = socket(AF_INET, SOCK_STREAM, 0);
        connect(s_socketfd, (struct sockaddr*) &addr, sizeof(addr));
        std::string s;
        std::cout << "client_cin: ";
        std::cin >> s;
        strcpy(sendbuf, s.c_str());
        send(s_socketfd, sendbuf, strlen(sendbuf), 0);
        std::cout << "client_send: " << sendbuf << std::endl;

        recv(s_socketfd, buf, sizeof(buf), 0);
        std::cout << "client_recv: " << buf << std::endl;

        close(s_socketfd);

    }

    return 0;
}