#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <cstdlib>
using namespace std;

const int BUFFER_SIZE = 1024;
static const char * status_line[2] = {"200 OK", "500 Internal server error"};

int main(int argc, char **argv)
{
    if(argc <= 3)
    {
        std::cout << "argc <= 3" << endl;
        exit(1);
    }

    const char * ip = argv[1];
    int port = atoi(argv[2]);

    const char * file_name = argv[3];

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr *) &address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 20);
    assert(ret != -1);

    struct sockaddr_in clnt;
    socklen_t clnt_len = sizeof(clnt);
    int connfd = accept(sock, (struct sockaddr *) &clnt, &clnt_len);

    if(connfd < 0)
    {
        cout << "errno = " << errno << endl;
        exit(-1);
    }
    else
    {
        char header_buf[BUFFER_SIZE]; //保存http应答
        memset(header_buf, '\0', sizeof(BUFFER_SIZE));

        char * file_buf; //目标文件缓存
        struct stat file_stat; //获取目标文件属性
        bool valid = true; //记录文件是否是有效文件
        int len = 0;
        if(stat(file_name, &file_stat) < 0)
        {
            valid = false;
        }
        else
        {
            if(S_ISDIR(file_stat.st_mode))
                valid = false;
            else if(file_stat.st_mode & S_IROTH)
            {
                int fd = open(file_name, O_RDONLY);
                file_buf = new char[file_stat.st_size + 1];
                memset(file_buf, '\0', file_stat.st_size + 1);
                if(read(fd, file_buf, file_stat.st_size) < 0)
                {
                    valid = false;
                }
            }
            else
                valid = false;
        }
        if(valid)
        {
            ret = snprintf(header_buf, BUFFER_SIZE - 1, "%s %s\r\n", "HTTP/1.1", status_line[0]);

            len += ret;
            ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "Content-Length: %d\r\n", file_stat.st_size);

            len+= ret;
            ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "%s", "\r\n");
            struct iovec iv[2];
            iv[0].iov_base = header_buf;
            iv[0].iov_len = strlen(header_buf);
            iv[1].iov_base = file_buf;
            iv[1].iov_len = file_stat.st_size;
            ret = writev(connfd, iv, 2); //将内容一并写出
        }
        else //如果目标文件无效 返回错误500
        {
            ret = snprintf(header_buf, BUFFER_SIZE - 1, "%s %s\r\n", "HTTP/1.1", status_line[1]);

            len += ret;
            ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "%s", "\r\n");
            send(connfd, header_buf, strlen(header_buf), 0);
        }
        close(connfd);
        delete[] file_buf;

    }
    close(sock);
    return 0;
}
