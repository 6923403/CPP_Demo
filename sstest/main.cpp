#include <iostream>
using namespace std;

int changek(int k)
{
    k = 9;
    return k;
}

void test1()
{
    int k = 10;

    changek(k);
    cout << "k: " << k << endl;
}

int changej(int &j)
{
    j = 9;
    return j;
}

void test2()
{
    int j = 10;
    changej(j);
    cout << "j: " << j << endl;
}

int changes(int *s)
{
    *s = 9;
    return *s;
}

int changep(int &p)
{
    p = 8;
    return p;
}


void test3()
{
    int s = 10;
    int *p = &s;
    cout << "*P1: " << *p << endl;
    changes(&s);
    cout << "*p2: " << *p << endl;
    changep(*p);
    cout << "s: " << s << "   P: " << *p << endl;
}

int main()
{
    test1();
    test2();
    test3();
}
