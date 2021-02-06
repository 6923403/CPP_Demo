#include <iostream>
#include <poll.h>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

const int BUF_SIZE = 1024;

int main(int argc, const char * argv[]) {
    if(argc <= 2)
    {
        std::cout << "argc < 2" << std::endl;
        exit(0);
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    
    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &client_addr.sin_addr);
    client_addr.sin_port = port;
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    int ret = connect(sockfd, (struct sockaddr* ) &client_addr, sizeof(client_addr));
    assert(ret >= 0);

    pollfd fds[2];
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].fd = sockfd;
    fds[1].events = POLLIN | POLLRDHUP;
    fds[1].revents = 0;
    
    char read_buf[BUF_SIZE];
    int pipefd[2];
    ret = pipe(pipefd);
    
    while(true)
    {
        //poll(<#struct pollfd *#>, <#nfds_t#>, <#int#>)
        ret = poll(fds, 2, -1);
        if(ret < 0)
        {
            std::cout << "poll failure" << std::endl;
            break;
        }
        
        if(fds[1].revents & POLLRDHUP)
        {
            std::cout << "server close the connection " << std::endl;
            break;
        }
        else if (fds[1].revents & POLLIN)
        {
            memset(read_buf, '\0', BUF_SIZE);
            recv(fds[1].fd, read_buf, sizeof(read_buf) + 1, 0);
            std::cout << read_buf << std::endl;
        }
        
        if(fds[0].revents & POLLIN)
        {
            /* 使用 splice将用户输入的数据直接写到sockfd上（零拷贝）*/
            ret = splice(0, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
            ret = splice(pipefd[0], NULL, sockfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        }
    }
    
    close(sockfd);

    return 0;
}
