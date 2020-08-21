#include <iostream>
using namespace std;


class Te
{
    public:
        Te te1();
        Te te2(int t2a);
};

Te Te::te1()
{
    cout << "te1" << endl;


Te Te::te2(int t2a)
{
    cout << "te2" << endl;
    cout << t2a << endl;
}

const int ma = 10;

int main()
{
    Te te;
    te.te1().te2(ma);
    //te.te2(ma).te1();
    return 0;
}

