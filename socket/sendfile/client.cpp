#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char filename[10] = {0};
    printf("Input save_filename: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "wb");

    if(fp ==NULL)
    {
        printf("Cannot Open file \n");
        exit(-1);
    }

    int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);

    connect(sock, (struct sockaddr *) &sockAddr, sizeof(sockAddr));

    char buffer[128] = {0};
    int nCount;
    while((nCount = read(sock, buffer, 128)) > 0)
    {
        fwrite(buffer, nCount, 1, fp);
    }
    printf("File transfer success \n");

    fclose(fp);
    close(sock);

    return 0;
}

