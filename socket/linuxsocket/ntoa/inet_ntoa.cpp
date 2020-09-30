#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

int main(int argc, char **argv)
{
    char l1[] = "1.2.3.4";
    char l2[] = "10.192.70.12";

    struct in_addr addr1;
    struct in_addr addr2, addr3;

    addr1.s_addr = inet_addr(l1);
    addr2.s_addr = inet_addr(l2);

    char * sz_Value1 = inet_ntoa(addr1);
    cout << "v1 = " << sz_Value1 << endl;

    char * sz_Value2 = inet_ntoa(addr2);
    cout << "v2 = " << sz_Value2 << endl;

    return 0;
}
