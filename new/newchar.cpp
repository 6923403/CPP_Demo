#include <iostream>
#include <memory>
#include <string>
#include <cstring>

using namespace std;

void test1()
{
    char *c1 = "abc";
    char *c2 = "def";
    string s1 = "To";
    string s2 = "Go";

    char *p = new char[strlen(c1) + strlen(c2) + 2];
    strcpy(p, c1); //copy
    strcat(p, c2); //append

    cout << p << endl;

    strcpy(p, (s1 + s2).c_str());
    cout << p << endl;

    delete [] p;
}

int main(int argc, char **argv)
{
    test1();

    return 0;
}