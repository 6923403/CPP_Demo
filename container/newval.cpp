#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string rep(string &s, string oldval, string newval)
{
    //string s = "thototho";
    //s = thoughtothough
    auto it1 = s.begin();
    auto it2 = newval.begin();
    auto it3 = newval.end();
    for(it1; it1 != s.end(); ++it1)
    {
        s,substr(it1, 3);
        if(s == oldval)
        {
            it1 = s.erase(it1, 3);
            it1 = s.insert(it1, it2, it3);
            advance(it1, 3);
        }
    }

    return s;
}

void te1()
{
    string s = "thototho";
    string oldval = "tho";
    string newval = "through";

    string qq = rep(s, oldval, newval);
    cout << qq << endl;

}

int main(int argc, char **argv)
{
    te1();

    return 0;
}
