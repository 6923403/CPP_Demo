#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <cstring>
#include <cassert>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

const int BUFFER_SIZE = 1024;
static int connfd;

void sig_urg(int sig)
{
    int save_errno = errno;
    char buf[BUFFER_SIZE];
    memset(&buf, '\0', sizeof(buf));

    int ret = recv(connfd, buf, BUFFER_SIZE - 1, MSG_OOB);
    std::cout << "recv: " << buf << std::endl;


    errno = save_errno;
}

void addsig(int sig, void (*sig_handler)(int))
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));

    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;

    sigfillset(&sa.sa_mask);
    assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char **argv)
{
    int port = 20999;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if((bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) || (listen(sockfd, 5) == -1) )
    {
        exit(0);
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    connfd = accept(sockfd, (struct sockaddr*) &client_addr, &client_addr_len);
    assert(connfd != -1);

    addsig(SIGURG, sig_urg);
    fcntl(connfd, F_SETOWN, getpid());
    char buffer[BUFFER_SIZE];
    int ret = 0;
    while(true) {
        memset(buffer, '\0', BUFFER_SIZE);
        ret = recv(connfd, buffer, BUFFER_SIZE-1, 0);
        if (ret <= 0)
            break;

        std::cout << "recv2: " << buffer << std::endl;
    }

    close(connfd);
    close(sockfd);

    return 0;
}
