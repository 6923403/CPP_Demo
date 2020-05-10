#include <iostream>
using namespace std;

class qq
{
    public:
        int k1;
        int k2;
};

int main(int argc, char **argv)
{
    qq *q1;
    q1->k1 = 10;
    *q1->k2 = 20;

    cout << q1->k1 << endl;

    cout << *q1->k2 << endl;
}
