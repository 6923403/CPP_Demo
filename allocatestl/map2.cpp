#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

void test1()
{
    map<string, size_t> word_count;
    set<string> exclude = {"the", "but", "and", "or", "an", "a", "The", "But", "And", "Or", "An", "A"};
    map<string, string> authors = {{"Joyce", "James"},
                                   {"Austen", "Jane"},
                                   {"Dickens", "Charles"}};
}

void test2()
{
    vector<int> ivec;
    for(vector<int>::size_type i = 0; i != 10; ++i)
    {
        ivec.push_back(i);
        ivec.push_back(i);
    }

    set<int> iset(ivec.begin(), ivec.end());
    multiset<int> miset(ivec.cbegin(), ivec.cend());
    cout << ivec.size() << endl;
    cout << iset.size() << endl;
    cout << miset.size() << endl;
}

void test3()
{
    map<string, vector<string>> family;
    string f_name, c_name;
    while([&]()->bool{cout << "姓氏: " << endl; return cin >> f_name && (f_name != "stop");}())
    {
        cout << "姓名: " << endl;
        while(cin >> c_name && (c_name != "stop"))
        {
            family[f_name].push_back(c_name);
        }
    }

    map<string, vector<string>>::iterator index;
    for(index = family.begin(); index != family.end(); ++index)
    {
        cout << index->first << ": ";
        vector<string>::iterator it1 = index->second.begin();
        for(it1; it1 != index->second.end(); ++it1)
            cout << *it1 << "  " << endl;
    }

    cout << endl;
}

int main(int argc, char **argv)
{
    test3();

    return 0;
}
