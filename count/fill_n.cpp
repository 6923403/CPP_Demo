#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
using namespace std;

void test1()
{
    vector<int> vec(10, 42);
    fill_n(back_inserter(vec), vec.size(), 0);

    cout << endl;
    for(auto s : vec)
    {
        cout << s << endl;
    }
}

void elimDups(vector<string> &sq)
{
    for(auto s1 : sq)
    {
        cout << s1 << "  ";
    }

    sort(sq.begin(), sq.end());
    auto end_unique = unique(sq.begin(), sq.end());

    cout << endl;
    for(auto s2 : sq)
        cout << s2 << "  ";
    cout << endl;
    sq.erase(end_unique, sq.end());

    for(auto s3 : sq)
        cout << s3 << "  " << endl;

}

void test2()
{
    vector<string> sq = {"aaa", "ssac", "zxc", "qwe", "zws", "rtg"};
    elimDups(sq);
}

int main(int argc, char **argv)
{
    test2();
    return 0;
}
