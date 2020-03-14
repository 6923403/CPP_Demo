#include <iostream>
#include "line.h"
using namespace std;

void test1()
{
    line h_line;
    h_line.setlen(7.5);
    cout << "Length of line: " << h_line.getlen() << endl;

    h_line.length = 20.6;
    cout << "Length of line: " << h_line.length << endl;

    int k;
    cin >> k;

}

int main(int argc, char **argv)
{
    test1();

    return 0;
}
