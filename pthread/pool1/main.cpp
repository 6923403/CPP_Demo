#include "pool.h"

int main(int argc, char** argv)
{
    Pool pool;
    pool.init(5);

    std::cout << "操作完成" << std::endl;

    return 0;
}