#include <iostream>
#include <string>

#include "Em.h"
using namespace std;

Employee::Employee()
{

}


void Employee::setperson()
{
    static int num = 100001;
    string _name;
    cin >> _name;
    name = _name;

    cardID = num;
    ++num;
}

void Employee::showperson()
{
    cout << name << "  " << cardID << endl;
}

