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

    auto it1 = s.begin();
    for(it1; it1 != s.end(); ++it1)
    {
        string tmp = (); 
        if(tmp.find_first_not_of(nval))
            cout << tmp << " "; 
    }
}

int main(int argc, char **argv)
{
    te2();

    return 0;
}
