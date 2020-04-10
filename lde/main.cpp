#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
using namespace std;

void test1()
{
    vector<int> q1(10, 22);
    if(!q1.empty())
    {
        q1.front() = 42;
        auto &v = q1.back();
        v = 55;
        auto v2 = q1.back();
        v2 = 10;
    }

    for(auto s : q1)
    {
        cout << s << endl;
    }

}

void test2()
{
    vector<string> ss;
    cout << ss.at(0);
}

int main()
{
    //test1();
    test2();
}
