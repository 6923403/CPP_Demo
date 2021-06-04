#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <memory>
#include <cstdlib>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
//http://www.wxdrillto.com/product/585.html

const int Buf_Size = 1024;

int main(int argc, char** argv)
{

    std::string ip = "122.114.57.135";
    const int port = 80;
    struct sockaddr_in addr;
    char buf[Buf_Size] = {};
    socklen_t addr_len;
    int ret = 0;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        std::cout << "连接失败" << std::endl;
        exit(0);
    }

    std::cout << "连接成功" << std::endl;

    char buf1[2048];
    char buf2[2048];
    memset(buf1, 0, sizeof(buf1));
    strcat(buf1, "theDataToPost");
    memset(buf2, 0, sizeof(buf2));

    strcat(buf2, "GET /product/585.html HTTP/1.1 \n");
    strcat(buf2, "Host: www.wxdrillto.com \n");
    strcat(buf2, "Accept-Language: zh-cn \n");
    strcat(buf2, "\n");
    strcat(buf2, buf1);
    strcat(buf2, "\r\n\r\n");
    std::cout << buf2 << std::endl;

    ret = write(sockfd, buf2, strlen(buf2));
    if (ret < 0) {
        std::cout << "发送失败" << std::endl;
    } else {
        std::cout << "发送成功, 发送字节: " << ret << std::endl;
    }

    fd_set t_set1;
    int h = 0;
    struct timeval tv;
    int n = 0;
    char buff[65536];

    FD_ZERO(&t_set1);
    FD_SET(sockfd, &t_set1);

    {

        tv.tv_sec = 0;
        tv.tv_usec = 0;
        h = 0;

        h = select(sockfd +1, &t_set1, NULL, NULL, &tv);
        std::cout << "--------------->" << std::endl;

        if(h < 0) {
            close(sockfd);
            std::cout << "select error" << std::endl;
            return 0;
        }
        else if(h >= 0)
        {
            memset(buff, 0, sizeof(buff));
            n = read(sockfd, buff, sizeof(buff) - 1);
            if(n == 0)
            {
                std::cout << "read error" << std::endl;
                return 0;
            }
        }

        std::cout << buff << std::endl;
    }

    close(sockfd);

    return 0;
}
