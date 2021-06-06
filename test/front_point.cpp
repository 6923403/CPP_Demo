#include <iostream>

struct A
{
    int a;
    char b;
};
int main(int argc, char** argv)
{
    A s = {
            .a = 10,
            .b = 'c',
    };
    std::cout << "s.a = " << s.a << " " << "s.b = " << s.b << std::endl;

    return 0;
}