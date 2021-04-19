#include "LStock.h"

void test()
{
    LStock s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.show();
    s.pop();
    s.pop();
    s.show();
}

int main(int argc, char** argv)
{
    test();
    return 0;
}
