#include <iostream>
#include "shape.h"
using namespace std;

void test1()
{
    Shape *shape;
    Rectangle rec(10, 7);
    Triangle tri(10, 5);

    shape = &rec;

    shape->area();

}

int main(int argc, char **argv)
{
    test1();
}
