#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void te1()
{
    ifstream in;
    in.open("1.txt", ios::binary);
        vector<string> vec;
        string data;
    if(in.is_open())
    {
        while(getline(in, data))
        {
            vec.push_back(data);
        }

    }
    for(auto s : vec)
        cout << s << endl;

    in.close();
}

void te2()
{
    ifstream in;
    in.open("1.txt", ios::binary);
    string data;
    vector<string> vec2;
    while(in >> data)
        vec2.push_back(data);

    for(auto s : vec2)
        cout << s << endl;

    in.close();
}


int main()
{
    te1();

    return 0;
}
