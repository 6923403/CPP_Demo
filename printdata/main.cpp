#include <iostream>
#include "printdata.h"
using namespace std;

void test1()
{
    Printdata pk;

    pk.print(100);
    pk.print(100.01);
    char *c = "ABC";

    pk.print(c);
}

int main(int argc, char **argv)
{
    test1();
}

