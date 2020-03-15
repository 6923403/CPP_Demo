#include <iostream>
using namespace std;

int main()
{
    int a[2] = {10, 20};
    int b[2] = {10, 20};

    int n = 2;

    for(int i = n - 1; i >= 0; i--)
    {
        for(int j = n - 1; j >= 0; j--)
        {
            cout << a[i] << b[j];
        }
    }
}
