#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;

void te1()
{
    list<int> v1 = {1, 4, 5, 6, 3, 1, 3, 6, 8, 8};

    vector<double> q1(v1.begin(), v1.end());
    vector<int> q2(v1.begin(), v1.end());

    for(auto &s1 : q1)
        cout << s1 << endl;

    for(auto &s2 : q2)
        cout << s2 << endl;
}

int main(int argc, char **argv)
{
    te1();
}
