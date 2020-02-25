#include <iostream>
#include "box.h"
using namespace std;

void Box::setlen(double len)
{
    cin >> len;
    length = len;
}

void Box::sethei(double hei)
{
    cin >> hei;
    height = hei;
}

void Box::setbre(double bre)
{
    cin >> bre;
    breadth = bre;

}

void Box::showre(double re)
{
    result = re;
    return length * breadth * height;
}

