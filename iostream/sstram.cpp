#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

void test1()
{
    vector<string> ss;
    ifstream in;
    in.open("1.txt");
    if(in)
    {
        string line;
        while(getline(in, line))
        {
            ss.push_back(line);
        }

    }

    for(int i = 0; i < ss.size(); ++i)
    {
        istringstream iss(ss[i]) ;
        string word;
        while(iss >> word)
        {
            cout << word << endl;
        }
    }

}

int main()
{
    test1();
}
