#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <netdb.h>
/*
 * struct servent
 * {
 *      char* s_name;       //服务名称
 *      char** s_aliases;   //服务的别名列表
 *      int s_port;         //端口
 *      char* s_proto;      //服务类型，tcp或udp
 *  };
 */

int main(int argc, char **argv)
{
    char *host = "101.132.159.69";
    struct hostent *hostinfo = gethostbyname(host);
    assert(hostinfo);

    struct servent *servinfo = getservbyname("daytime","tcp");
    assert(servinfo);
    std::cout << servinfo->s_name << "  " << servinfo->s_port << " " << servinfo->s_proto << " " << servinfo->s_aliases << std::endl;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = servinfo->s_port;
    //因为h_addr_list本身就是网络字节序的地址列表，故直接赋值
    address.sin_addr = *(struct in_addr*)*hostinfo->h_addr_list;

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    int result = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
    assert(result != -1);
    char buffer[128];
    result = read(sockfd, buffer, sizeof(buffer));
    assert(result > 0);

    buffer[result] = '\0';
    std::cout << "the day time is:" << buffer << std::endl;
    close(sockfd);

    return 0;
}