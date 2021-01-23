#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char** argv)
{
    char* strdir = getcwd(nullptr, 256);
    std::cout << "strdir = " << strdir << std::endl;

    strncat(strdir, "./resources", 16);
    std::cout << "strdir2 = " << strdir << std::endl;

    return 0;
}

