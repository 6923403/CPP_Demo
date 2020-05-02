#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

template<typename T, typename U>
int find(T &v1, U &v2)
{
    int n;
    auto s1 = v1.begin();
    for(s1; s1 != v1.end(); ++s1)
    {
        if(*s1 == v2)
            return 1;
    }

    return 2;
}

int main(int argc, char **argv)
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<string> ls = {"ass", "sss", "qqq", "ddd", "zzz", "vvv", "qaqa"};
    int q;
    string p;
    cin >> q;
    cout << endl;
    cin >> p;
    cout << find(vec, q) << endl;
    cout << find(ls, p) << endl;
}
