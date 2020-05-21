#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string rep(string &s, string oldval, string newval)
{
    //string s = "thoto";
    //s = thoughto
    int size1 = oldval.size();
    auto it1 = s.begin();
    auto it2 = newval.begin();
    auto it3 = newval.end();
    for(it1; it1 <= (s.end() - 2); ++it1)
    {
        s.substr(it1 - s.begin(), size1);
        if(s == oldval)
        {
            it1 = s.erase(it1, it1 + size1);
            s.insert(it1, newval);
            advance(it1, 2);
        }
    }

    return s;
}

void te1()
{
    string s = "thoto";
    string oldval = "tho";
    string newval = "through";

    rep(s, oldval, newval);
    cout << s << endl;

}

int main(int argc, char **argv)
{
    te1();

    return 0;
}
