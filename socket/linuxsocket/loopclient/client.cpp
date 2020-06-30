#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    struct sockaddr_in cl_addr;
    memset(&cl_addr, 0, sizeof(cl_addr));

    cl_addr.sin_family = PF_INET;
    cl_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    cl_addr.sin_port = htons(1234);

    const int BUFSIZE = 100;

    char bufread[BUFSIZE] = {0};
    char bufwrite[BUFSIZE] = {0};

    while(true)
    {
        int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (struct sockaddr *) &cl_addr, sizeof(cl_addr));

        printf("Input a string: ");
        scanf("%s ", bufwrite);
        write(sock, bufwrite, sizeof(bufwrite));

        read(sock, bufread, sizeof(bufread) - 1);

        printf("Message form server: %s \n", bufread);

        memset(bufwrite, 0, sizeof(bufwrite));
        memset(bufread, 0, sizeof(bufread));

        close(sock);
    }

    return 0;
}
