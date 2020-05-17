#include <iostream>
#include <list>
#include <forward_list>
#include <string>
using namespace std;

void listset(forward_list<string> &ls, string s1, string s2)
{
    auto it1 = ls.begin();
    s1 = "vvv";
    s2 = "kkk";
    bool flag = false;
    while(it1 != ls.end())
    {
        if(*it1 == s1)
        {
            it1 = ls.insert_after(it1, s2);
            ++it1;
            flag = true;
        }
        else
            ++it1;

#if 0
        if(!flag)
        {
            ls.insert_after(it1, s2);
        }
#endif
    }

}


void te1()
{
    forward_list<string> ls = {"aaa", "vvv", "bbb", "ccc", "www"};
    string s1, s2;
    listset(ls, s1, s2);

    for(auto &s : ls)
        cout << s << "  ";
}

int main(int argc, char **argv)
{
    te1();
    return 0;
}
