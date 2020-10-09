#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <cassert>

using namespace std;

int main(int argc ,char **argv)
{
    assert(argc == 2);
    char *host = argv[1];
    
    struct hostent * hostinfo = gethostbyname(host);
    cout << *hostinfo << endl;
    assert(hostinfo);

    struct servent * servinfo = getservbyname("datime", "tcp");
    cout << "port = " << ntohs(servinfo->s_port) << endl;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = servinfo->s_port;

    address.sin_addr = *(struct in_addr *) *hostinfo->h_addr_list;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int result = connect(sockfd, (struct sockaddr *) &address, sizeof(address));
    assert(result != -1);

    char buffer[128];
    result = read(sockfd, buffer, sizeof(buffer));
    assert(result > 0);
    buffer[result] = '\0';
    cout << "daytime = " << buffer << endl;

    close(sockfd);
    return 0;
}
