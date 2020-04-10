#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

void test1()
{
    map<string, size_t> word_count;
    string word;
    while(cin >> word && word != "stop")
    {
        ++word_count[word];
    }
    for(const auto &w : word_count)
        cout << w.first << "  occurs " << w.second << ((w.second > 1) ? " times" : " time") << endl;
}

void test2()
{
    map<string, size_t> word_count;
    string word;
    while(cin >> word && word != "stop")
    {
        string::iterator it1;
        for(it1 = word.begin(); it1 != word.end(); it1++)
        {
            *it1 = tolower(*it1);
        }
        word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());
        ++word_count[word];
    }

    for(const auto &w : word_count)
        cout << w.first << "  occurs " << w.second << ((w.second > 1) ? " times" : " time") << endl;
}

int main(int argc, char **argv)
{
    test2();
}
