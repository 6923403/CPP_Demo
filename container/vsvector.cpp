#include <vector>
#include <string>
#include <iostream>
using namespace std;

void te1()
{
    vector<int> v2;

    v2.at(0);
    v2.push_back(2);
    v2.front();
    vector<int>::iterator it1 = v2.begin();
    cout << *it1 << endl;
}

int main(int argc, char **argv)
{
    te1();
}
