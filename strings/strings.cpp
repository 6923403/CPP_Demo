#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv)
{
    const char *cp = "Hello World!!!";
    char noNull[] = {'H', 'i'};
    string s1(cp);
    string s2(noNull, 2);
    string s3(noNull);
    string s4(cp + 6, 5);
    string s5(s1, 6, 5);
    string s6(s1, 6);
    string s7(s1, 6, 20);
    /*
     * out_of_range
     * string s8(s1, 16); 
     */

    string k("hello world");
    string k2 = k.substr(0, 5);
    string k3 = k.substr(6);
    string k4 = k.substr(6, 11);
    /*
     * out_of_range
     * string k5 = k.substr(12);
     */

    vector<char> p(6, 'a');
    string p2(p.begin(), p.end());
    cout << p2 << endl;
}
