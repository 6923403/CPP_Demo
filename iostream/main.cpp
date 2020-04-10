#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void test1()
{
    vector<string> vec;
    ifstream read;
    read.open("1.txt", ios::binary);
    if(read)
    {
        string s;
        while(getline(read, s))
        {
            vec.push_back(s);
        }
    }

    vector<string>::iterator it1 = vec.begin();

    ofstream out;
    out.open("2.txt");
    for(it1; it1 != vec.end(); it1++)
    {
        cout << *it1 << "  " << endl;
        out << *it1 << endl;
    }
}

int main()
{
    test1();
    return 0;
}

