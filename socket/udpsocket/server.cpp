#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int ser_sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(1234);
    bind(ser_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    struct sockaddr_in cl_addr; 
    socklen_t m_size;
    int nSize = sizeof(sockaddr);
    char buffer[128];
    while(true)
    {
        /*
         * ssize_t recvfrom(int sock, void *buf, size_t nbytes, int flags, struct sockadr *from, socklen_t *addrlen);  //Linux
         * int recvfrom(SOCKET sock, char *buf, int nbytes, int flags, const struct sockaddr *from, int *addrlen);  //Windows
         * sock：用于接收UDP数据的套接字；
         * buf：保存接收数据的缓冲区地址；
         * nbytes：可接收的最大字节数（不能超过buf缓冲区的大小）；
         * flags：可选项参数，若没有可传递0；
         * from：存有发送端地址信息的sockaddr结构体变量的地址；
         * addrlen：保存参数 from 的结构体变量长度的变量地址值。
         */
        int strlen = recvfrom(ser_sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&cl_addr, &m_size);

        /*
         * ssize_t sendto(int sock, void *buf, size_t nbytes, int flags, struct sockaddr *to, socklen_t addrlen);  //Linux
         * int sendto(SOCKET sock, const char *buf, int nbytes, int flags, const struct sockadr *to, int addrlen);  //Windows
         * sock：用于传输UDP数据的套接字；
         * buf：保存待传输数据的缓冲区地址；
         * nbytes：带传输数据的长度（以字节计）；
         * flags：可选项参数，若没有可传递0；
         * to：存有目标地址信息的 sockaddr 结构体变量的地址；
         * addrlen：传递给参数 to 的地址值结构体变量的长度。
         */
        sendto(ser_sock, buffer, strlen, 0, (struct sockaddr *)&cl_addr, m_size);
    }

    close(ser_sock);

    return 0;
}

