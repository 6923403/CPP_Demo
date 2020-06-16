#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void * func1(void * args)
{
    cout << "a" << endl;
    sleep(1);
}

void * func2(void * args)
{
    cout << "b" << endl;
    sleep(1);
}

void * func3(void * args)
{
    cout << "c" << endl;
    sleep(1);
}

void test1()
{
    const int NUM_THREADS = 3;

    pthread_t tid1, tid2, tid3;
    for(int i =0; i < 10; i++)
    {
        int ret = pthread_create(&tid1, NULL, func1, NULL);
        int ret2 = pthread_create(&tid2, NULL, func2, NULL);
        int ret3 = pthread_create(&tid3, NULL, func3, NULL);
    }

    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    test1();

    return 0;
}
