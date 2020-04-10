#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
using namespace std;

int acc(vector<int> ls)
{
    int num;
    num = accumulate(ls.cbegin(), ls.cend(), 0);
    return num;

}

int main(int argc, char **argv)
{
    vector<int> lk = {12, 52, 61, 23, 12, 55, 11, 22, 66, 77};
    int num = acc(lk);
    cout << num << endl;

}
