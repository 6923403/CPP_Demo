#include <iostream>
#include "box.h"
using namespace std;

void test1()
{
    Box Box1;
    Box Box2;
    double volume = 0.0;

    Box1.setlen(1);
    Box1.sethei(2);
    Box1.setbre(3);
    Box1.showre(1);
}

int main(int argc, char **argv)
{
    test1();
}
