#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void test1()
{
    vector<string> words = {"qwex", "fcsaaaa", "asz", "rfs", "kjfa", "oue", "pks", "qww", "jjf", "suj"};
    /*
     * stable_sort(words.begin(), words.end(), 
                [](const string &a, const string &b)
                {
                    return a.size() < b.size();
                });
                */
stable_sort(words.begin(), words.end(), 
                [](const string &a, const string &b)
                {
                    return a < b;
                });
       
    for(auto &s : words)
    {
        cout << s << endl;
    }
}

void test2()
{
    vector<string> words = {"qwex", "fcsaaaa", "asz", "rfs", "kjfa", "oue", "pks", "qww", "jjf", "suj"};
    string sz = "aaa";
    auto wc = find_if(words.begin(), words.end(), 
            [sz](const string &a)
            {
                return a.size() > sz.size();
            });
    auto count = words.end() - wc;
    cout << "count = " << count << " " <<" words, "
        << "sz = " << sz << endl;
}

int main()
{
    test2();
    return 0;
}
