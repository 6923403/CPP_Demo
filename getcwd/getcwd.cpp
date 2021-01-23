#include <iostream>
#include <unistd.h>

int main(int argc, char** argv)
{
    char* strdir = getcwd(nullptr, 256);
    std::cout << "strdir = " << strdir << std::endl;

    return 0;
}

