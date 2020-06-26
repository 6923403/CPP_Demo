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
    serv_addr.sin_port = htons(1234);

    /*
     * 本函数向服务iq发起请求 服务器ip port 保存在sockaddr_in中
     */
    connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    char buf[40];

    /*
     * read从套接字文件中读取数据
     */
    read(sock, buf, sizeof(buf) -1);

    printf("Message form server: %s \n", buf);
    close(sock);

    return 0;
}
