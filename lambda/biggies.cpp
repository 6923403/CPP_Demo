#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void biggies(vector<string> &words, 
        vector<string>::size_type sz, 
        ostream &os = cout, char c = ' ')
{
    for_each(words.begin(), words.end(),
            [&os, c](const string &s)
            {
                os << s << c;
            });
}

void test1()
{
    vector<string> words = {"asdsa", "asqsss", "cxcsa", "ererew", "aasdwq"};
    vector<string>::size_type sz;
    char c = ' ';
    biggies(words, sz, cout, c);
}

int main(int argc, char **argv)
{
    test1();
}
