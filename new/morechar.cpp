#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main(int argc, char **argv)
{
    string s;
    cin >> s;

    char *p = new char[10];
    strcpy(p, s.c_str());

    cout << p << endl;
    
    delete [] p;
}
