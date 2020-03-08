#include <iostream>
#include <pthread.h>
using namespace std;

#define NUM_THREADS 5

void *say_hello(void *args)
{
    static int h = 1;
    cout << "Hello Run" << "  h = " << h << endl;
    h++;
    return 0;
}

void *say_go(void *args)
{
    static int a = 1;
    cout << "Say Go" << "  a = "<< a <<  endl;
    a++;
    return 0;
}

int main(int argc, char **argv)
{
    pthread_t tids[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        cout << "i = " << i << endl;
        //线程ID, 线程参数， 调用的函数， 传入的函数参数
        int ret = pthread_create(&tids[i], NULL, say_hello, NULL);
        int ret2 = pthread_create(&tids[3], NULL, say_go, NULL);
        if(ret != 0)
        {
            cout << "pthread_create_ error: error code = " << ret << endl;
        }
    }
    
    pthread_exit(NULL);
}
