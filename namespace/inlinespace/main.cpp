#include "test.h"

#include <iostream>

int main(int argc, char **argv)
{
    int a = 100, b = 2;
    int num = X::Y::foo(a, b);
    std::cout << num << '\n';
    return 0;
}

