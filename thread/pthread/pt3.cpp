#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

void* ptintf_hello_world(void * tid);

int main(int argc, char **argv)
{
    pthread_t threads[10];
    int status, k = 10, i = 0;
    cout << "Main here. threads = " << i << endl;

    for(int i = 0; i < 10; i++)
    {
        /*
         * int pthread_create(pthread_t *thread, const pthread_attr_t *attr,                                void *(*start_routine) (void *), void *arg);
         */

        status = pthread_create(&threads[i], NULL, ptintf_hello_world, NULL);
        if(status)
        {
            cout << "ERROR: pthread_create failed " << status << endl;
            exit(-1);
        }
    }

    cout << "start join" << endl;
    for(int j = 0; j < 10; j++)
    {
        pthread_join(threads[j], NULL); 
    }

    return 0;
}

void* ptintf_hello_world(void * tid)
{
    cout << "Hello world  " << endl;

    pthread_exit(NULL);

    return NULL;
}
