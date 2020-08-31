#include <stdio.h>
#include <cstring>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char **argv) 
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in ser_addr;
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = PF_INET;
    ser_addr.sin_addr.s_addr = inet_addr("server_ip");
    ser_addr.sin_port = htons(server_port);

    connect(sock,(struct sockaddr *) &ser_addr, sizeof(ser_addr));

    char buf[100];
    
    printf("Input a string: ");
    scanf("%s", buf);
    write(sock, buf, sizeof(buf));

    char bufrecv[100] = {0};

    read(sock, bufrecv, sizeof(bufrecv) -1);

    printf("Message form server: %s \n", bufrecv);

    close(sock);
    return 0;
}
