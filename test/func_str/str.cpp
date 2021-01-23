#include <iostream>
#include <string>
using namespace std;

void fun(std::string str)
{
    cout << str << endl;
}

int main(int argc, char** argv)
{
    fun("test");

    cout << "end" << endl;
    return 0;
}
