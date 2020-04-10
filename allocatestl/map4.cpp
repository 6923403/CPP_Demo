#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <set>
using namespace std;

void test1()
{
    vector<int> ivec = {2, 4, 6, 8, 2, 4, 6, 8};
    set<int> set2;
    set2.insert(ivec.cbegin(), ivec.cend());
    set2.insert({1, 3, 5, 7, 1, 3, 5, 7});

    map<string, int> word_count;

    word_count.insert({word, 1});
    word_count.insert(make_pair(word, 1));
    word_count.insert(pair<string, size_t>(word, 1));
    word_count.insert(map<string, size_t>::value_type(word, 1));
}

void test2()
{
    map<string, size_t> word_count;
    string word;
    while(cin >> word)
    {
        ++word_count.insert(word, 0).first->second;
    }

}

#if 0
void test3()
{
    map<string, vector<int>> vec;
    pair<string, vector<int>>;
    pair<map<string, vector<int>>::iterator, bool>;
}

void test4()
{
    if(word_count.erase(removal_word))
        cout << "ok: " << removal_word << " removed\n";
    else
        cout << "oops: " << removal_word << "not found!\n";

    auto cnt = authors.erase("Barth, John");

}
#endif

void test5()
{
    map<string, size_t> word_count;

    word_count["Anna"] = 1;
    cout << word_count["Anna"];
    ++word_count["Anna"];
    cout << word_count["Anna"];
}

int main(int argc, char **argv)
{
    test5();

    return 0;
}
