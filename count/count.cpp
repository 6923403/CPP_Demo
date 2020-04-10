#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
using namespace std;

int f_int(vector<int> qa, int s)
{
    int pos = 0;
    pos = count(qa.begin(), qa.end(), s);
    return pos;
}

int f_string(list<string> qs, string ss)
{
    int pos;
    pos = count(qs.cbegin(), qs.cend(), ss);
    return pos;
}

int main(int argc, char **argv)
{
#if 0
    vector<int> qa = {11, 25, 66, 45, 12, 22, 33, 6, 78, 9, 112, 55, 22, 23, 66, 22, 55, 22, 555, 44, 22};
    int s;
    cin >> s;
    int num = f_int(qa, s);
#endif
    list<string> qs = {"as", "za", "za", "sd", "qqqqza", "sd", "zx", "za"};
    string ss;
    cin >> ss;
    int num2 = f_string(qs, ss);
    cout << num2 << endl;
}
