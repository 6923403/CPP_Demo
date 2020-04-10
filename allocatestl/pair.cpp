#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <map>
using namespace std;

void test1()
{
    pair<string, string> anon;
    pair<string, size_t> word_count;
    pair<string, vector<int>> line;
    pair<string, string> author{"James", "Joyce"};

}

#if 0
void test2()
{
    pair<string, int> process(vector<string> &v)
    {
        if(!v.empty())
            return (v.back(), v.back.size());
        else
            return pair<string, int>();
    }
}
#endif

void test3()
{
    vector<pair<string, int>> vec(12);
    string str;
    int i = 0;
    int val;
    int j = 0;

    while(cin >> str && str != "stop")
    {
        vec[i].first = str;
        ++i;
    }

    while(cin >> val && val != 666)
    {
        vec[j].second = val;
        ++j;
    }

    vector<pair<string, int>>::iterator it1 = vec.begin();
    for(it1; it1 != vec.end(); ++it1)
    {
        cout << it1->first << "  " << it1->second << endl;
    }


}

void test4()
{
    map<string, vector<string>> family;
    vector<pair<string, string>> child;
    string first_name, child_name, _birthday;

begin:
    while([&]()->bool{
            cout << "cin first_name: ";
            cin >> first_name && first_name != "stop";
            }())
    {
        while([&]()->bool{
                cout << "cin child_name: ";
                cin >> child_name && child_name != "stopc";
                }())
        {
            family[first_name].push_back(child_name);
            while([&]()->bool{
                cout << "cin brithday: ";
                cin >> _birthday && _birthday != "stopb";
                }())
            {
                child.push_back(make_pair(child_name, _birthday));
                goto begin;
            }
        }
    }

    map<string, vector<string>>::iterator mapi;
    for(mapi = family.begin(); mapi != family.end(); ++mapi)
    {
        cout << mapi->first << ": ";
        vector<string>::iterator it1 = mapi->second.begin();
        for(it1; it1 != mapi->second.end(); ++it1)
        {
            cout << *it1 << " ";
        }

    }

    cout << endl;
    vector<pair<string, string>>::iterator it1 = child.begin();
    cout << "Child: ";
    for(it1; it1 != child.end(); ++it1)
        cout << it1->first <<  "  " << it1->second;
}

int main(int argc, char **argv)
{
    test4();

    return 0;
}
