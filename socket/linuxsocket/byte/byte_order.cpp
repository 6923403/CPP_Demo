#include <iostream>

using namespace std;

void byte_order()
{
    union
    {
        short value;
        char union_bytes[sizeof(short)];

    } test;
    test.value = 0x0102;
    if((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2))
    {
        cout << "big endian " << endl;
    }
    else if((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1))
    {
        cout << "little endian " << endl;
    }
    else
    {
        cout << "unknown... " << endl;
    }

    //little endian 
}

int main(int argc, char **argv)
{
    byte_order();

    return 0;
}
