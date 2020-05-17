#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

void te1()
{
    vector<string> v1;
    list<const char *> ll(10, "s");

    v1.assign(ll.begin(), ll.end());

    for(auto &s : v1)
        cout << s << endl;
}

int main(int argc, char **argv)
{
    te1();
}

