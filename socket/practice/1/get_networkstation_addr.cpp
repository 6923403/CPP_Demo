#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cout << "argv = NULL " << std::endl;
        exit(-1);
    }

    struct hostent * host = gethostbyname(argv[1]);
    if(!host)
    {
        std::cout << "get " << argv[1] << " ip_addr error " << std::endl;
        exit(-1);
    }

    for(int i = 1; host->h_addr_list[i]; i++)
    {
        std::cout << "ip_addr_" << i << ":  " << inet_ntoa(*((struct in_addr *)host->h_addr_list[i])) << std::endl;;
    }

    return 0;
}
