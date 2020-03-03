#include <iostream>
#include <shape.h>
using namespace std;

Shape::Shape(int a = 0, int b = 0)
{
    width = a;
    height = b;
}

int Shape::area()
{
    cout << "Parent class area: " << endl;
    return 0;
}

Rectangle Rectangle::Rectangle(int a = 0, int b = 0):Shape(a, b)
{
}

int Rectangle::area()
{
    cout << "Rectangle class area: " << endl;
    return (width * height);
}

Triangle Triangle::Triangle(int a = 0, int b = 0):Sape(a, b)
{

}

int Shape::area()
{
    cout << "Trangle class area: " << endl;
    return (width * height / 2);
}


