#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>

#include "text.h"
using namespace std;

int main(int argc, char **argv)
{
    ifstream in;
    in.open("123.txt", ios::binary);

    int err = 1;
    if(!in)
    {
        cerr << "error open file, please inspect, err = " << err;;
        exit(1);
    }

    return 0;
}

//我输了。     
