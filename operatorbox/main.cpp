#include <iostream>
#include "opbox.h"
using namespace std;

void test1()
{
    Box box1;
    Box box2;
    Box box3;
    double volume = 0.0;

    box1.setLength(6.0);
    box1.setBreadth(7.0);
    box1.setHeight(5.0);
    
    box2.setLength(12.0);
    box2.setBreadth(13.0);
    box2.setHeight(10.0);

    volume = box1.getVolume();
    cout << "Volume of box1: " << volume << endl;

    //box2体积
    volume - box2.getVolume();
    cout << "Volume of box2: " << volume << endl;

    box3 = box1 + box2;
    volume = box3.getVolume();
    cout << "Volume of box3: " << volume << endl;
}

int main(int argc, char **argv)
{
    test1();
}
