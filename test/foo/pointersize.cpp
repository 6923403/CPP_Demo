#include <iostream>
using namespace std;

class A
{
    int &a;
};

class B
{
};

int main()
{
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    int i = 10;
    int *p = &i;

    cout << sizeof(p) << endl

    return 0;
}
