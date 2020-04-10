#include <iostream>
#include <string>
using namespace std;

namespace first_space
{
    void func()
    {
        cout << "inside first_space " << endl;
    }
}

namespace second_space
{
    void func()
    {
        cout << "inside_second_space "<< endl;
    }
}

void test1()
{
    first_space::func();

    second_space::func();
}

int main(int argc, char **argv)
{
    test1();
}
