#include <iostream>
using namespace std;

void q(int *p)
{
    cout << *p << endl;
    cout << &p << endl;
    cout << p << endl;
}

int main()
{
    int p = 10;
    int *p2 = &p;
    q(&p);
}
