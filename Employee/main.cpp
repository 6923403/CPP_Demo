#include <iostream>

#include "Em.h"
using namespace std;

int main(int argc, char **argv)
{
    Employee p1;
    cout << "set person" << endl;
    p1.setperson();

    Employee p2;
    p2.setperson();

    cout << "show person" << endl;

    p1.showperson();

    p2.showperson();
}
