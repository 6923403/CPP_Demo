#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char **argv)
{
    ifstream in;
    in.open("1.txt", ios::binary);
    string data;
    vector<string> vec;
    istringstream ss;
    for(int i = 0; i < vec.size(); i++)
    {
        ss(vec[i]);
    }

    string word;
    while(ss >> word)
        cout << word << endl;


    return 0;
}
