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

int main()
{
    test1();
    return 0;
}
