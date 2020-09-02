#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

void* ptintf_hello_world(void * tid);

int main(int argc, char **argv)
{
    pthread_t thread;
    int status, i = 10;
    cout << "Main here. threads = " << i << endl;

    status = pthread_create(&thread, NULL, ptintf_hello_world, (void *)i);

    pthread_join(thread, NULL); //

    if(status != 0)
    {
        cout << "pthread_create returned error code: " << status << endl;
        exit(0);
    }

    return 0;
}

void* ptintf_hello_world(void * tid)
{
    cout << "Hello world = " << tid << endl;
    exit(0);
}
