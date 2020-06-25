#include <iostream>
#include <cstdlib>
#include <thread>
using namespace std;

const int numpth = 5;

void *tk(void *th)
{
    int tid = *((int *) th);
    cout << "Hello Runoob! 线程ID, " << tid << endl;
    pthread_exit(NULL);
}

void test1()
{
    pthread_t threads[numpth];
    int indexes[numpth];
    int rc;
    for(int i = 0; i < numpth; ++i)
    {
        cout << "main(): 创建线程, " << i << endl;
        indexes[i] = i;
        rc = pthread_create(&threads[i], NULL, tk, (void *)&(indexes[i]));
        if(rc)
        {
            cout << "Error " << i << endl;
            exit(-1);

        }

    }
    pthread_exit(NULL);
}

int main()
{
    test1();
}
