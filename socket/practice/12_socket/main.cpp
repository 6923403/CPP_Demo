#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

const int BUFFER_SIZE = 2048;
static const char *status_line[2] = {"200 OK", "500 Internal server error"};

/*
 * struct iovec
 * {
 * void *iov_base;  //指向一个缓冲区，这个缓冲区是存放readv所接收的数据或是writev将要发送的数据
 * size_t iov_len;  //接收的最大长度以及实际写入的长度
 * };
 */

int main(int argc, char **argv)
{
    int port = 20999;
    const char *file_name = "331.txt";

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    int ret = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(sockfd, 10);
    assert(ret != -1);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    int connfd = accept(sockfd, (struct sockaddr*) &client_addr, &client_addr_len);
    if(connfd < 0)
    {
        std::cout << "coonect sockfd error" << std::endl;
    }
    else
    {
        char header_buf[BUFFER_SIZE];
        memset(header_buf, 0, BUFFER_SIZE);
        char *file_buf = NULL;                    //用于存放目标文件内容的缓存
        struct stat file_stat;                    //用于获取目标文件的属性
        bool valid = true;                        //目标文件是否有效
        int len = 0;                              //记录header_buf当前已使用的字节空间

        if(stat(file_name, &file_stat) < 0) {     //目标文件不存在
            valid = false;
        }
        else {
            if(S_ISDIR(file_stat.st_mode)) {  //目标文件是目录
                valid = false;
            }
            else if (file_stat.st_mode & S_IROTH) {               //当前用户是否有读权限，相对于目标文件
                int fd = open(file_name, O_RDONLY);
                file_buf = new char[file_stat.st_size + 1];
                memset(file_buf, '\0', file_stat.st_size + 1);

                if (read(fd, file_buf, file_stat.st_size) < 0) {
                    valid = false;
                }
            }
            else {
                valid = false;
            }
        }

        if (valid) {   //目标文件有效
            ret = snprintf(header_buf, BUFFER_SIZE-1,
                           "%s %s\r\n",
                           "HTTP/1.1", status_line[0]);

            len += ret;
            ret = snprintf(header_buf+len, BUFFER_SIZE-1-len,
                           "content-Length: %ld\r\n",
                           file_stat.st_size);

            len += ret;
            ret = snprintf(header_buf+len, BUFFER_SIZE-1-len,
                           "%s", "\r\n");

            //将header_buf和file_buf的内容一并写出
            struct iovec iv[2];
            iv[0].iov_base = header_buf;
            iv[0].iov_len = strlen(header_buf);
            iv[1].iov_base = file_buf;
            iv[1].iov_len = file_stat.st_size;

            //fprintf(stderr, "read %s success\nsending %s file to client...\n", file_name, file_name);

            ret = writev(connfd, iv, 2);   //集中写

        }
        else {     //目标文件无效
            ret = snprintf(header_buf, BUFFER_SIZE-1,
                           "%s %s\r\n",
                           "HTTP/1.1", status_line[1]);

            len += ret;
            ret = snprintf(header_buf+len, BUFFER_SIZE-1-len,
                           "%s", "\r\n");

            //fprintf(stderr, "read %s failed\nsending error message to client...\n", file_name);

            send(connfd, header_buf, strlen(header_buf), 0);
        }

        close(connfd);

        if (file_buf != NULL) {
            delete[] file_buf;
            file_buf = NULL;
        }

    }
    close(sockfd);

    return 0;
}