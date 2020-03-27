#include <iostream>
#include <string>
#include <forward_list>
#include <vector>
#include <algorithm>
using namespace std;

void test1()
{
    forward_list<int> s1 = {1, 2, 3, 4, 5, 6, 7, 18, 29};
    auto iter = s1.begin();
    auto prev = s1.before_begin();

    while(iter != s1.end())
    {
        if(*iter % 2 == 1)
        {
            iter = s1.insert_after(prev, *iter);
            advance(iter, 2);
            advance(prev, 2);
        }
        else
        {
            iter = s1.erase_after(prev);
        }
    }

    for(auto k : s1)
    {
        cout << k << endl;
    }
}

int main(int argc, char **argv)
{
    test1();
}
