/*
 * https://blog.csdn.net/qq_36573828/article/details/82784425
 */
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <cassert>

using namespace std;

int main(int argc, char **argv)
{
    const int max_arr_size = 1024;
    string ip = "127.0.0.1";
    int port = 11206;
    if(argc > 1)
    {
        port = atoi(argv[1]);
    }
    cout << "Start" << endl;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(serv_sock != 0);

    int ret = bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    assert(ret != -1);

    ret = listen(serv_sock, 20);
    int connfd;
    while(true)
    {
        cout << "************\t" << endl;
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        connfd = accept(serv_sock, (struct sockaddr *) &client, &client_len);
        if(connfd < 0)
        {
            cout << "Error = 1" << endl;
        }
        else
        {
            off_t offset = 0;
            off_t len = 0; // 必须初始化0, 不然下次重入时，会被旧值覆盖
            char head[1024], sizehd[1024];

            struct sf_hdtr m_hdtr;
            struct iovec m_headers;
            struct iovec m_trailers;
            m_headers.iov_base = head;
            m_headers.iov_len = strlen(head);
            //trailers.iov_base = (void *)"file---rn"; //todo: don't recv sometimes ??
            //trailers.iov_len = 9;
            m_hdtr.headers = &m_headers;
            m_hdtr.hdr_cnt = 1;
            m_hdtr.trailers = NULL;
            m_hdtr.trl_cnt = 0;

            char request[max_arr_size];
            recv(connfd, request, 1024, 0);
            request[strlen(request) + 1] = '\0';
            cout << request << "Successful ." << endl;
            char buf[max_arr_size] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";
            int s = send(connfd, buf, strlen(buf), 0);

            int fd = open("hello.html", O_RDONLY);
            //sendfile(connfd, fd, NULL, 2500);
            sendfile(fd, connfd, offset, &len, &m_hdtr, 0);

            close(fd);
            close(connfd);
        }
    }

    return 0;
}
