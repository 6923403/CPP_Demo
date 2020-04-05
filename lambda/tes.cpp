#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>
#include <fstream>
#include <iterator>
using namespace std;

void test1()
{
    vector<int> vec = {1, 21, 2, 32, 32, 12, 44, 24, 42, 112, 42};
    vector<int> sk;
    istream_iterator<int> end;
    sort(vec.begin(), vec.end());

    copy(vec.begin(), end, back_inserter(sk));

    for(const auto &s : vec)
    {
        cout << s << endl;
    }

}

int main(int argc, char **argv)
{
    test1();
}
    
