#include <iostream>
#include "fbox.h"
using namespace std;

void Box::setwidth(double wid)
{
    width = wid;
}

void printwidth(Box box)
{
    cout << "Wid: " << box.width << endl;
}
