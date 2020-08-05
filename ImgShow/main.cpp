#include "img.h"
#include <iostream>

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cout << "Please cin your img path ." << '\n';
        return -1;
    }

    for(int i = 1; i < argc; i++)
    {
        if(Is::showfile(argv[i]))
            return 0;
    }

    std::cout << "The end ." << std::endl;

    return 0;
}
