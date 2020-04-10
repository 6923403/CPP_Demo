#include <iostream>
#include <iterator>
#include <vector>
#include <list>
using namespace std;

void test1()
{
    vector<int> vec = {100, 22, 301, 32, 93, 20, 02};
#if 0
    for(auto it1 = vec.rbegin(); it1 != vec.rend(); it1++)
    {
        cout << *it1 << "  ";
    }
#endif
    list<int> k;
    copy(vec.rbegin() - 3, vec.rend() - 2, back_inserter(k));

    for(const auto &s : k)
        cout << s << "  ";
}

void test2()
{

}

int main(int argc, char **argv)
{
    test1();
}
