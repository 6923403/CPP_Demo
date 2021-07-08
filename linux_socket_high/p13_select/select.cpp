#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>


int main(int argc, char **argv)
{
    int port = 20999;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd != -1);

    int ret = bind(listenfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);
    ret = listen(listenfd, 10);
    assert(ret != -1);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int connfd = accept(listenfd, (struct sockaddr*) &client_addr, &client_addr_len);
    if(connfd < 0)
    {
        std::cout << "connfd < 0" << std::endl;
        close(listenfd);
        exit(0);
    }
    char remote_addr[INET_ADDRSTRLEN];
    std::string con_ip = inet_ntop(AF_INET, &client_addr.sin_addr, remote_addr, INET_ADDRSTRLEN);
    int con_port = ntohs(client_addr.sin_port);
    std::cout << "conncet with ip: " << con_ip << " and port: " << con_port << std::endl;

    char buf[1024];
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);

    //设置接收处带数据
    int reuseaddr = 1;
    setsockopt(connfd, SOL_SOCKET, SO_OOBINLINE, &reuseaddr, sizeof(reuseaddr));

    while(true)
    {
        memset(buf, '\0', sizeof(buf));

        //每次调用select前都要重新设置，因为事件发生后，文件描述符集合会被内核修改
        FD_SET(connfd, &read_fds);
        FD_SET(connfd, &exception_fds);

        ret = select(connfd + 1, &read_fds, NULL, &exception_fds, NULL);
        std::cout << "select one" << std::endl;

        if (ret < 0) {
            std::cout << "selection failed" << std::endl;
            break;
        }

        if (FD_ISSET(connfd, &read_fds)) {
            ret = recv(connfd, buf, sizeof(buf)-1, 0);
            if (ret <= 0)
                break;

            std::cout << "get " << ret << " bytes of normal data: " << buf << std::endl;
        }
        else if (FD_ISSET(connfd, &exception_fds)) {	//接收外带数据
            ret = recv(connfd, buf, sizeof(buf)-1, MSG_OOB);
            if (ret <= 0)
                break;

            std::cout << "get " << ret << " bytes of normal data: " << buf << std::endl;
        }
    }
    close(connfd);
    close(listenfd);

    return 0;
}