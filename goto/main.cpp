#include <iostream>
#include <string>
using namespace std;

int get_size()
{
    static int k = 5;
    k++;

    return k;
}

int get_size_t()
{
    static int q = 5;
    q++;

    return q;
}

int main()
{
begin:
    int sz = get_size();
    if(sz <= 10)
    {
        cout << sz << endl;
        goto begin;
    }

    int f = 0;
    while(f < 10)
    {
        f = get_size_t();
        cout << f << endl;
    }
}
