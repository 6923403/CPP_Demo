#include <iostream>
#include <string>
using namespace std;

void te1()
{
    string s = "issthoggggg";
    string oldval = "tho";
    string newval = "though";

    int oldsize = oldval.size();
    int newsize = newval.size();

    for(int i = 0; i <= s.size() - 3;)
    {
        if(s.substr(i, oldsize) == oldval)
        {
            s.replace(i, oldsize, newval);
            i += (newsize - oldsize);
        }
        else
            ++i;
    }

    cout << s << endl;
}

int main(int argc, char **argv)
{
    te1();
}
