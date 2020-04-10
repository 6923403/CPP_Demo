#include <iostream>
#include "shape.h"
using namespace std;

void Shape::setWidth(int w)
{
    width = w;
}

void Shape::setHeight(int h)
{
    height = h;
}

int PaintCost::getCost(int area)
{
    return area * 70;
}

int Rectangle::getArea()
{
    return (width * height);
}
