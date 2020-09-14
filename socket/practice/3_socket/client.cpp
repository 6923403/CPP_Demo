#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char **argv)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(12121);

    connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    char buf[40];

    read(sock, buf, sizeof(buf) - 1);

    cout << "Message is: " << buf << endl;

    sleep(100);
    close(sock);
    return 0;
}
