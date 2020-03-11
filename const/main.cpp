#include <iostream>
using namespace std;

void test1()
{
    const int bufsize = 512;
    
//    const int i = get_size();
    const int j = 42;
}

void test2()
{
    int i = 42;
    const int ci = i;
    int j = ci;
}
int func();

extern const int bufSize = func();

int func()
{
    return 7;
}

int main(int argc, char **argv)
{

    cout << bufSize << endl;
    test2();
}
