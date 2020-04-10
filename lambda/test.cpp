#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

void test1()
{
    int q = 10, q2 = 20;
    auto s = [](int &q1, int &q2)
    {
        return q1 + q2;
    };

    cout << s(q, q2) << endl;
}

int sum(const int &q1, const int &q2)
{
    auto s = [q1](int q2)
    {
        return q1 + q2;
    };

    return s(q2);
}

void test2()
{
    int k1 = 5, k2 = 8;
    cout << sum(k1, k2);
}

int main(int argc, char **argv)
{
    test2();

    return 0;
}
