#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <numeric>
using namespace std;

void test1()
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 1};
    list<int> ls = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto  v1 = count(vec.begin(), vec.end(), 1);

    vector<string> vstr = {"aaa", "aaa", "ccc", "ddd", "eee", "aaa"};
    auto v2 = count(vstr.begin(), vstr.end(), "aaa");
    cout << v2 << endl;
}

void test2()
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 1};
    int sum = accumulate(vec.begin(), vec.end(), 0);

    vector<string> vstr = {"a", "b", "c", "d"};
    string sum2 = accumulate(vstr.begin(), vstr.end(), string(""));
    cout << sum2 << endl;
}

void test3()
{
    //vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 1};
    //fill(vec.begin(), vec.end(), 0);

}

int main(int argc, char **argv)
{
    test2();

    return 0;
}
