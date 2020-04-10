#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
using std::placeholders::_1;

bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}

void test1()
{
    vector<string> words = {"asd", "aqwe", "cxcsa", "wwwwwwwwwww", "gfghfhff"};
    
    auto check6 = bind(check_size, _1, 6);

    string s = "hello";
    bool bl = check6(s);

    vector<string>::size_type sz;
    auto wc = find_if(words.begin(), words.end(),
            bind(check_size, _1, sz));

    cout << *wc << endl;
}

bool check_s(const int &s, string::size_type sz)
{
    if(s > sz)
        return true;
    else
        return false;
}


void test2()
{
    string s = "aaaaasdasda";
    vector<int> k = {3, 2, 22, 5, 7};
    string::size_type _len = s.size();
    auto wq = find_if(k.begin(), k.end(), bind(check_s, _1, _len));
    cout << *wq << endl;
}

int main(int argc, char **argv)
{
    test2();
}
