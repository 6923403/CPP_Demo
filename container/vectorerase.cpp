#include <iostream>
#include <vector>
#include <list>
using namespace std;

void te1()
{
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};

    /*
     * for(auto &q : ia)
        cout << q << endl;
     */
    vector<int> vec(ia, ia + 9);
    list<int> ls(ia, ia + 9);

    auto it1 = vec.begin();
    auto it2 = ls.begin();
    while(it1 != vec.end())
    {
        if((*it1) % 2 == 0)
        {
            it1 = vec.erase(it1);
        }
        else
            ++it1;
    }

    while(it2 != ls.end())
    {
        if((*it2) % 2 == 1)
        {
            it2 = ls.erase(it2);
        }
        else
            ++it2;
    }

    for(auto &s1 : vec)
        cout << s1 << "  ";

    cout << endl;

    for(auto &s2 : ls)
        cout << s2 << "  ";
}

int main(int argc, char **argv)
{
    te1();
    return 0;
}



