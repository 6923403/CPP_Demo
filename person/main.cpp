#include <iostream>
#include "person.h"
using namespace std;

void te1()
{
    Person one;
    Person two("AAA");
    Person three("SS", "abc");
    cout << "one 1" << endl;
    one.Show();

    cout << "2" << endl;
    cout << endl;
    one.FormalShow();

    cout << "two 1" << endl;
    two.Show();

    cout << "two 2" << endl;
    cout << endl;
    two.FormalShow();

    cout << "three 1" << endl;
    three.Show();

    cout << "three 2" << endl;
    cout << endl;
    three.FormalShow();
}


int main(int argc, char **argv)
{
    te1();

    return 0;
}
