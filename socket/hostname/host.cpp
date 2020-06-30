#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char **argv)
{
    char * name = argv[1];
    struct hostent *hptr;
    hptr = gethostbyname(name);
    if(!hptr)
    {
        puts("Get host error. \n");
        exit(-1);
    }

    for(int i = 0; hptr->h_aliases[i]; i++)
    {
        printf("aliases %d: %s \n", i + 1, hptr->h_aliases[i]);
    }

    printf("Address type: %s \n", (hptr->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

    //IP地址
    for(int i=0; hptr->h_addr_list[i]; i++){
        printf("IP addr %d: %s\n", i+1, inet_ntoa( *(struct in_addr*)hptr->h_addr_list[i] ) );
    }

    return 0;
}
