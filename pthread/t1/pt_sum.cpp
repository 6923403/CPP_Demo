#include <iostream>
#include <stdio.h>
#include <cstring>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

char buf[100] = {0};
int flag;
sem_t sem;

// 子线程程序，作用是统计buf中的字符个数并打印
void *func(void*arg)
{
// 子线程首先应该有个循环
// 循环中阻塞在等待主线程激活的时候，子线程被激活后就去获取buf中的字符
// 长度，然后打印；完成后再次被阻塞
    sem_wait(&sem);
    while(flag==0)
    {

    cout << "str_len = " << strlen(buf) << endl;
    memset(buf, 0, sizeof(buf));
    sem_wait(&sem);
    }
    flag = 1;
    pthread_exit(NULL);
}


int main(int argc, char **argv)
{
    int ret = -1;
    pthread_t pid;
    sem_init(&sem, 0, 0);

    while(scanf("%s",buf))
    {
        if(!strncmp(buf,"end",3))
        {
            flag == 1;
            sem_post(&sem);
            break;
        }
        sem_post(&sem);
    }

    ret = pthread_create(&pid, NULL, func, NULL);
    if(ret != 0)
    {
        cout << "pthread_create error = 1" << endl;
        exit(-1);
    }

    cout << "等待回收子线程" << endl;
    ret = pthread_join(pid, NULL);
    if(ret != 0)
    {
        cout << "pthread_join error " << endl;
        exit(-1);
    }

    cout << "子线程回收成功" << endl;
    sem_destroy(&sem);
    return 0;
}
