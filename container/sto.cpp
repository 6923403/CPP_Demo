#include <iostream>
#include <string>
#include <vector>
using namespace std;

void te1()
{
    vector<string> vec(5, "10.1");
    int sum = 0;
    double sum2 = 0.0;
    for(int i = 0; i < vec.size(); i++)
    {
        sum += stoi(vec[i]);
        sum2 += stod(vec[i]);
    }

    cout << sum << endl;
    cout << sum2 << endl;
}

int main(int argc, char **argv)
{
    te1();

    return 0;
}
