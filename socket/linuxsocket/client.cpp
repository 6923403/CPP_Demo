#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    /*
     * 创建套接字
     */
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    /*
     * 向服务器(ip-port) 发起请求
     */
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(20999);

    /*
     * 本函数向服务ip发起请求 服务器ip port 保存在sockaddr_in中
     * int connect(int sock, struct sockaddr *serv_addr, socklen_t addrlen);  //Linux
     * int connect(SOCKET sock, const struct sockaddr *serv_addr, int addrlen);  //Windows
     * sock 为 socket 文件描述符，addr 为 sockaddr 结构体变量的指针，addrlen 为 addr 变量的大小，可由 sizeof() 计算得出。
     */
    connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    char buf[40];

    /*
     * read从套接字文件中读取数据
     * fd 为要读取的文件的描述符，buf 为要接收数据的缓冲区地址，nbytes 为要读取的数据的字节数。
     */
    read(sock, buf, sizeof(buf) -1);

    printf("Message form server: %s \n", buf);
    close(sock);

    return 0;
}
