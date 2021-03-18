#include "pool.h"

int main(int argc, char** argv)
{
    Pool pool;
    pool.init(5);
    Task* task = new Task[5];
    bool flag = false;

    for(int i = 0; i < 5; i++)
    {
        pool.add_pool(&task[i]);
        flag = pool.back_destroy();
        if(flag)
            break;
    }


    delete[] task;
    std::cout << "操作完成" << std::endl;

    return 0;
}