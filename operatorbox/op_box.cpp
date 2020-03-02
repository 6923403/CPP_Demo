#include <iostream>
#include "op_box.h"
using namespace std;

double Box::getVolume(void)
{
    return length * breadth * height;
}

void Box::setLength(double len)
{
    length = len;
}

void Box::setBreadth(double bre)
{
    breadth = bre;

}

void Box::setHeight(double hei)
{
    height = hei;
}

Box Box::operator+(const Box &b)
{
    Box box;
    box.length = this->length + b.length;
    box.breadth = this->breadth + b.breadth;
    box.height = this->height + b.height;
    return box;
}
