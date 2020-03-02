#include <iostream>
#include "printdata.h"
using namespace std;

void Printdata::print(int i)
{
    cout << "int = " << i << endl;

}

void Printdata::print(double f)
{
    cout << "double = " << f << endl;
   
}

void Printdata::print(char c[])
{
    cout << "char = " << c << endl;
}
