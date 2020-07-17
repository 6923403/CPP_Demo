#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
 * rdbuf()可以实现一个流对象指向的内容用另一个流对象来输出
 */

void te1()
{
    ifstream infile("1.txt");
    cout << infile.rdbuf();
}

void te2()
{
    fstream infile("1.txt", ios::in);
    fstream outfile("2.txt", ios::out);

    if(infile.is_open())
    {
        if(outfile.is_open())
        {
            outfile << infile.rdbuf();

            infile.close();
            outfile.close();
        }
    }
}

void init()
{
    fstream in("1.txt", ios::in);
    if(in.is_open())
    {
        string q;
        in >> q;
        cout << q << endl;
    }
}

int main(int argc, char **argv)
{   
    te2();
    return 0;
}

