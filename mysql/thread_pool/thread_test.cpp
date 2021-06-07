#include <iostream>

#include "../log/easylogging.h"
#include "Thread_Pool.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv)
{
    Thread_Pool<int> pool(1, 0, 3);
    return 0;
}