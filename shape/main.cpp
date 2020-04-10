#include <iostream>
#include "shape.h"
using namespace std;

int main(int argc, char **argv)
{
    int area;
    Rectangle Rect;
    Rect.setWidth(5);
    Rect.setHeight(7);

    area = Rect.getArea();
    cout << "Total area: " << Rect.getArea() << endl;
    cout << "All Cost: " << Rect.getCost(area) << endl;
}
