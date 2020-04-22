#include <iostream>
using namespace std;

int main()
{
    int a = 100;
    {
        a = 10;
        cout << a << endl;
    }
        cout << a << endl;
}
