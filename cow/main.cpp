#include <iostream>
#include <string>
#include "cow.h"
using namespace std;

void te1()
{
    Cow cow1("hehehe", "eat", 123.4);
    Cow cow2("heihei", "drink", 321.2);
    Cow cow3(cow2);
    Cow cow4 = cow1;

    cow1.ShowCow();
    cow2.ShowCow();
    cow3.ShowCow();
    cow4.ShowCow();

}

int main(int argc, char **argv)
{
    te1();

    return 0;
}
