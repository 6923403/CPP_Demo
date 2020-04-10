#include <iostream>
#include <string>
using namespace std;

int handle_y(string q)
{
    const string alphabet =  "abcdefghijklmnopqrstuvwxyz";
    const int num = "1234567890";
    int pos;
    while((pos = find_first_of(alphabet, pos)) != string::npos)
    {
        cout << pos << "  " << s[pos] << endl;
        ++pos;
    }
}

int main(int argc, char **argv)
{
    string q("ab2c3d7R4E6");
    handle_y(q);
}
