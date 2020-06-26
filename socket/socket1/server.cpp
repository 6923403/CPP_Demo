#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    /*
     * 创建套接字
     * int socket(int af, int type, int protocol);
     */
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /*
     * 将套接字、ip、端口绑定
     */
    struct sockaddr_in serv_addr;

    /*
     * 每个字节用0填充
     */
    memset(&serv_addr, 0, sizeof(serv_addr));

    /*
     * 使用IPV4
     */
    serv_addr.sin_family = AF_INET;

    /*
     * 具体的ip地址
     */
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /*
     * 端口号
     */
    serv_addr.sin_port = htons(1234);

    /*
     * serv_sock与指定IP Port绑定 保存在sockaddr_in结构体中
     */
    bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    /*
     * 进入监听状态 等待用户发起请求
     * 被动监听
     */
    listen(serv_sock, 20);

    /*
     * 接受客户端请求
     */
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    /*
     * 客户端发起请求前 暂停运行到本函数
     */
    int clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);

    /*
     * 向客户端发送数据
     */
    char str[] = "Hello World!";

    /*
     * 向客户端发送数据
     */
    write(clnt_sock, str, sizeof(str));

    /*
     * 关闭套接字
     */
    close(clnt_sock);
    close(serv_sock);

    return 0;
}
