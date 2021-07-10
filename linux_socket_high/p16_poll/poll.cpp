#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/uio.h>

const int USER_LIMIT = 512;		//最大用户数量
const int BUFFER_SIZE = 64;		//读缓冲区的大小
const int FD_LIMIT = 65535;		//文件描述符数量限制

struct client_data
{
    sockaddr_in address;		//客户端地址
    char *write_buf;			//发送到客户端的缓存区
    char buf[BUFFER_SIZE];	//客户端接收的缓存区
};

//设置非阻塞
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

//忽略SIGPIPE信号
static int ignore_sigpipe()
{
    struct sigaction act;

    if (sigaction(SIGPIPE, (struct sigaction*)NULL, &act) == -1)
        return -1;

    if (act.sa_handler == SIG_DFL) {
        act.sa_handler = SIG_IGN;
        if (sigaction(SIGPIPE, &act, (struct sigaction*)NULL) == -1)
            return -1;
    }

    return 0;
}


int main(int argc, char **argv)
{
    if (ignore_sigpipe() == -1)
        return 1;

    int port = 20999;
    int ret = 0;
    int error;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    std::cout << "server strart" << std::endl;

    int reuse = 1;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    assert(ret != -1);

    ret = bind(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    assert(ret != -1);

    ret = listen(sockfd, 10);
    assert(ret != -1);

    //客户端数组，每个socket连接获得一个这样的对象，socket值作为下标索引。
    client_data *users = new client_data[FD_LIMIT];
    //虽然已分配了足够多的client_data对象，但为了提高poll性能，仍然有必要限制用户数量
    pollfd fds[USER_LIMIT + 1];

    //当前用户连接数
    int user_counter = 0;

    for(int i = 0; i <= USER_LIMIT; ++i)
    {
        fds[i].fd = -1;
        fds[i].events = 0;
    }
    fds[0].fd = sockfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;

    while(true)
    {
        ret = poll(fds, user_counter+1, -1);
        assert(ret > -1);

        for(int i = 0; i < user_counter+1; ++i)
        {
            if((fds[i].fd == sockfd) && fds[i].revents & POLLIN)
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                int connfd;
                while (((connfd = accept(sockfd, (struct sockaddr*)&client_address, &client_addrlength)) == -1) && (connfd == EINTR));
                assert(connfd != -1);

                //如果请求太多，关闭新到的连接
                if (user_counter >= USER_LIMIT) {
                    const char *info = "too many users, please later\n";
                    std::cout << info << std::endl;

                    send(connfd, info, strlen(info), 0);
                    close(connfd);
                    continue;
                }

                user_counter++;
                //添加新连接的客户端到用户数组
                users[connfd].address = client_address;
                setnonblocking(connfd);

                //将新连接的客户端加入轮询
                fds[user_counter].fd = connfd;
                fds[user_counter].events = POLLIN | POLLRDHUP | POLLERR;
                fds[user_counter].revents = 0;

                std::cout << "comes a new user: " << connfd << " now have: " << user_counter << " users" << std::endl;
            }
            else if(fds[i].revents & POLLRDHUP)
            {
                //客户端关闭连接，则服务端也关闭对应的连接，并将用户总数减1
                //将最后一个连接数据复制到当前位置，删除原数据
                users[fds[i].fd] = users[fds[user_counter].fd];

                close(fds[i].fd);
                fds[i] = fds[user_counter];
                i--;
                user_counter--;
                std::cout << "a client left" << std::endl;
            }
            else if (fds[i].revents & POLLIN) {
                int connfd = fds[i].fd;
                memset(users[connfd].buf, '\0', BUFFER_SIZE);

                ret = recv(connfd, users[connfd].buf, BUFFER_SIZE - 1, 0);
                if (ret < 0) {
                    //如果读取错误，则关闭连接
                    if (errno != EAGAIN) {
                        std::cout << "client: " << connfd << " recv error" << std::endl;
                        close(connfd);
                        users[fds[i].fd] = users[fds[user_counter].fd];
                        fds[i] = fds[user_counter];
                        i--;
                        user_counter--;
                    }
                }
                else if (ret == 0) {
                    std::cout << "client: " << connfd << " code should not come to here" << std::endl;
                }
                else {
                    //如果接收到客户数据，则通知其他连接写数据
                    for (int j = 1; j <= user_counter; ++j)
                    {
                        if (fds[j].fd == connfd)
                            continue;
                        fds[j].events |= ~POLLIN;
                        fds[j].events |= POLLOUT;
                        users[fds[j].fd].write_buf = users[connfd].buf;
                    }
                }
            }
            else if (fds[i].revents & POLLOUT)
            {
                int connfd = fds[i].fd;
                if (!users[connfd].write_buf)
                    continue;
                ret = send(connfd, users[connfd].write_buf, strlen(users[connfd].write_buf), 0);
                users[connfd].write_buf = NULL;

                //写完数据后，需要重新注册可读事件
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
        }
    }
    delete[] users;
    close(sockfd);

    return 0;
}