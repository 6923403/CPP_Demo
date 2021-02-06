#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

const int MAX_USER = 5;
const int BUF_SIZE = 1024;
const int FD_SIZE = 65535;

struct client_data
{
    sockaddr_in addr;
    char* write_buf;
    char buf[BUF_SIZE];
};

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "use port error " << std::endl;
        exit(0);
    }
    int port = atoi(argv[1]);
    int ret = 0;
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    
    //bind(<#int#>, <#const struct sockaddr *#>, <#socklen_t#>)
    ret = bind(listenfd, (struct sockaddr* ) &serv_addr, sizeof(serv_addr));
    assert(ret != -1);
    
    ret = listen(listenfd, 5);
    assert(ret != -1);
    
    client_data* users = new client_data[FD_SIZE];
    pollfd fds[MAX_USER];
    int user_counter = 0;
    for(int i = 0; i <= MAX_USER; i++)
    {
        fds[i].fd = -1;
        fds[i].events = 0;
    }
    fds[0].fd = listenfd;
    fds[0].events = POLLIN | POLL_ERR;
    fds[0].revents = 0;

    while (true) {
        ret = poll(fds, user_counter + 1, -1);
        if(ret < 0)
        {
            std::cout << "poll failure" << std::endl;
            break;
        }
        
        for(int i = 0; i < user_counter + 1; i++)
        {
            if((fds[i].fd == listenfd) && (fds[i].revents & POLLIN))
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int connfd = accept(listenfd, (struct sockaddr*) &client_addr, &client_addr_len);
                if(connfd < 0)
                {
                    std::cout << "errno is " << errno << std::endl;
                    continue;
                }
                
                if(user_counter >= MAX_USER)
                {
                    const char* info = "too many users \n";
                    std::cout << info << std::endl;
                    send(connfd, info, strlen(info), 0);
                    close(connfd);
                    continue;
                }
                
                user_counter++;
                users[connfd].addr = client_addr;
                setnonblocking(connfd);
                fds[user_counter].fd = connfd;
                fds[user_counter].events = POLL_IN | POLLRDHUP | POLL_ERR;
                
            }
        }
    }

    close(listenfd);
    return 0;
}
