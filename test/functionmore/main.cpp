#include <iostream>

#include "test.h"
using namespace std;

int main(int argc, char **argv)
{
    unsigned w, h;
    unsigned error = de::decode(w, h);
    cout << error << endl;
    return 0;
}
