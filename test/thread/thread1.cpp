#include <iostream>
#include <pthread.h>
using namespace std;

int tall = 0;

void * func(void * args)
{
    for(int i = 0; i <= 50; i++)
    {
        tall += 1;
    }
    cout << "tall = " << tall << endl;
    return 0;
}

void test1()
{
    const int NUM_THREADS = 2;
    pthread_t tids[NUM_THREADS];
    for(int i = 0; i < 2; i++)
    {
        int ret = pthread_create(&tids[i], NULL, func, NULL);
        if(ret != 0)
        {
            cout << "pthread_create error: error_code = " << ret << endl;
        }
    }
    pthread_exit(NULL);
    cout << "tall = " << tall << endl;
}

int main(int argc, char **argv)
{
    test1();

    return 0;
}
