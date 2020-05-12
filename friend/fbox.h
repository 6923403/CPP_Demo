#ifndef FBOX_H
#define FBOX_H

#include <iostream>
using namespace std;

class Box
{
    friend void printwidth(Box box);
    double width;
    public:
    void setwidth(double wid);

};

#endif
