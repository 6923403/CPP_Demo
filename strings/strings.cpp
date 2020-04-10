#include <string>
#include <iostream>
#include <vector>
using namespace std;

void test1()
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

void test2()
{
    string s = "some string", s2 = "some other string ";
    s.insert(0, s2);
    s2.insert(0, s2, 0, s2.size());
    cout << s << endl;
    cout << s2 << endl;
}

void ine(string &m, string &z1, string &z2)
{
    int zs1 = z1.size();
    int zs2 = z2.size();
    auto it1 = m.begin();
    int ms = m.size();

    for(it1; it1 <= (ms - zs1); it1++)
    if(m.substr(it1, it1 + zs1) == z1)
    {
        m.erase(it1, zs1);
        m.insert(it1, 0, z2);
    }
}

void test3()
{
    string m = "71axzz5552";
    string z1 = "axzz";
    string z2 = "5552";
    ine(m, z1, z2);
    cout << m << endl;
}

int main(int argc, char **argv)
{
    test3();
}
