#include <iostream>
#include <vector>
#include <string>
using namespace std;

void te1()
{
    vector<char> v1 = {'a', 'b'};
    string s1(v1.begin(), v1.end());
    cout << s1 << endl;
}


int main(int argc, char **argv)
{
    te1();
}
