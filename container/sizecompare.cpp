#include <iostream>
#include <vector>
#include <list>
using namespace std;

template<typename T, typename Y>
bool compare(T a1, Y a2)
{
    if(a1.size() > a2.size())
        return true;

    return false;
}

template<typename T, typename Y>
bool comparevalue(T a1, Y a2)
{
    auto it1 = a1.begin();
    auto it2 = a2.begin();
    for(it1; it1 != a1.end() && it2 != a2.end(); ++it1, ++it2)
    {
        if(*it1 != *it2)
            return false;
    }

    return true;
}
    

void te1()
{
    vector<int> v1, v2;
    v1.push_back(1);
    v1.push_back(1);

    v2.push_back(1);

    list<int> l1;
    l1.push_back(1);
    l1.push_back(1);
    l1.push_back(1);
    l1.push_back(1);

//    bool flag = compare(v1, l1);
    bool flag = comparevalue(v1, v2);
    if(flag)
        cout << "111" << endl;
    else
        cout << "222" << endl;
}

int main(int argc, char **argv)
{
    te1();
}
