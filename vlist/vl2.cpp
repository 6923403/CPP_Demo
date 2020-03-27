#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <forward_list>
using namespace std;

void test1()
{
    int ia[] = {0, 1, 2, 3, 5, 7, 8, 13, 21, 55, 66};

    vector<int> qa(ia, ia + 1);
    list<int> kl(ia, ia + 1);
//    earse...
}

void test2()
{
    forward_list<int> s1{1, 10, 5, 8, 7, 12, 15};
    auto it1 = s1.before_begin();
    auto it2 = s1.begin();

    while(it2 != s1.end())
    {
        if((*it2) % 2 == 1)
            s1.erase_after(it1);
        else
        {
            it1 = it2;
            ++it2;
        }

    }

    for(auto c : s1)
        cout << c << endl;
}

int main()
{
    test2();
}
