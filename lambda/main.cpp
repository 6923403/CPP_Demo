#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

void test1()
{
    vector<string> qq = {"asd", "xxxxx", "zqq", "qwe", "wer", "asdqw"};
#if 0
    stable_sort(qq.begin(), qq.end(), [](const string &s1, const string &s2)
            {
                return s1.size() < s2.size();
            });
#endif

    int sz = 5;
    partition(qq.begin(), qq.end(), [sz](string &s1){
                if(s1.size() > sz)
                    return true;
                else
                    return false;
            });
    for(auto s : qq)
    {
        cout << s << "   " << endl;
    }

}

string make_plural(int q, const string &s1, const string &s2)
{
    return (q > 1) ? s1 + s2 : s1;
}

void test2()
{
    vector<string> qq = {"asd", "xxxxx", "zqq", "qwe", "wer", "asdqw", "word"};
    int sz = 4;

    auto wc = find_if(qq.begin(), qq.end(), [sz](const string &q)
            {
                return q.size() > sz;
            });

    auto count = qq.end() - wc;
    cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" <<  endl;
}

void test3()
{
    vector<string> word = {"asdz", "vdqvv", "zxcgbf", "tbggfdd"};
    int sz = 5;
    auto wc = find_if(word.begin(), word.end(), [sz](const string &q)
            {
                return q.size() > sz;
            });

    for_each(wc, word.end(), [](const string &s)
            {
                cout << s << "  ";
            });

    cout << endl;
}

int main(int argc, char **argv)
{
    test3();
}
