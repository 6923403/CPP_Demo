#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <arpa/inet.h>

using namespace std;

int main()
{
    struct in_addr addr;
    if(inet_pton(AF_INET, "127.0.0.1", &addr.s_addr) == 1)
        cout << std::hex << addr.s_addr << endl;

    char str[20];
    if(inet_ntop(AF_INET, &addr.s_addr, str, sizeof(str)))
        cout << str << endl;

    return 0;
}
