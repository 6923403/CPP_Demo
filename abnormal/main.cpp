#include <iostream>
#include <exception>
using namespace std;

double division(int a, int b)
{
    if(b == 0)
    {
        throw "Division by zero condition";

    }
    return (a / b);
}

void test1(){
    int x = 50;
    int y = 0;
    double z = 0;

    try
    {
        z = division(x, y);
        cout << z << endl;
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
    }
}

struct MyException: public exception
{
    const char* what() const throw()
    {
        return "C++ Exception";
    }
};

void test2()
{
    try
    {
        throw MyException();
    }
    catch(MyException &e)
    {
        cout << "My Exception caught" << endl;
        cout << e.what() << endl;
    }
    catch(exception &e)
    {
        cout << "other" << endl;
    }
}

int main(int argc, char **argv)
{
    test2();
}
