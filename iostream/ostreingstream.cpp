#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#if 0
void test1()
{
    for(const auto &entry : people)
    {
        ostringstream formatted, badNums;
        for(const auto &nums : entry.phones)
        {
            if(valid(nums))
            {
                badNums << " " << nums;
            }
            else
                formatted << " " << format(nums);
        }
        if(badNums.str().empty())
            os << entry.name << " "
                << formatted.str() << endl;
        else
            cerr << "input error: " << entry.name
                << "  invalid number(s) " << badNums.str() << endl;
    }
}
#endif

class Personinfo
{
    public:
    string name;
    vector<string> phones;
};

void te3()
{
    ifstream in("in.txt");
    ofstream outfile("out.txt", ios::app);

    string line, word;
    vector<Personinfo> people;

    while(getline(in, line))
    {
        Personinfo info;
        istringstream record(line);
        record >> info.name;

        while(record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }

    for(const auto &a : people)
    {
        ostringstream ostr;
        for(const auto &b : a.phones)
        {
            ostr << " " << b;
        }

        outfile << a.name << " " << ostr.str() << endl;
    }
}


int main(int argc, char **argv)
{
    te3();
}
