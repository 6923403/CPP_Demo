#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

void test1()
{
    vector<int> sk = {1221, 112, 333, 42, 422, 1202, 22, 112, 33, 22,11, 333};
    list<int> ls;
    unique_copy(sk.begin(), sk.end(), back_inserter(ls));

    for(const auto &s : ls)
        cout << s << "  " << endl;
}

void test2()
{
    vector<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> k1, k2, k3;
    copy(s.begin(), s.end(), inserter(k1, k1.begin()));
    copy(s.begin(), s.end(), back_inserter(k2));
    copy(s.begin(), s.end(), front_inserter(k3));

    for(auto s1 : k1)
        cout << s1 << "  ";

    cout << endl;

    for(auto s2 : k2)
        cout << s2 << "  ";

    cout << endl;

    for(auto s3 : k3)
        cout << s3 << "  ";
} 

int main(int argc, char **argv)
{
    test2();
    return 0;
}

