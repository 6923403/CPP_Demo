#include <iostream>
#include <string>
using namespace std;

void te1()
{
    string num = "1234567890";
    string val = "ab2c3d7r4e6";
    int n1 = val.find_first_of(num);
    int n2 = val.find_first_not_of(num);

    cout << n1 << "  " << n2 << endl;
}

void te2()
{
    string nval = "dfpglkqh";
    string s = "asdqwfdphinriskal";
    int q;
#if 0
    for(q = 0; q < s.size(); q++)
    {
        q = s.find_first_of(nval);
        if(q)
        {
            s.substr(0, q);
            cout << s << endl;
        }
        else
        {
            cout << s << endl;
            q = s.size() + 1;
        }
    }
#endif

}

int main(int argc, char **argv)
{
    te2();

    return 0;
}
