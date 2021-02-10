#include <iostream>
#include <cstring>
#include <semaphore.h>
#include <pthread.h>

static int num;

static sem_t m_sem;
static sem_t n_sem;

/*
 * 调用sem_init函数时，操作系统将创建信号量对象，此对象中记录着“信号量值”（semaphoreValue）整数。
 * 该值在调用sem_post函数时增1，调用semwait函数时减1。
 * 但信号量的值不能小于0，因此，在信号量为0的情况下调用sem一vait函数时，调用函数的线程将进人阻塞状态（因为函数未返回）。
 * 当然，此时如果有其他线程调用sem一post函数，信号量的值将变为1，而原本阻塞的线程可以将该信号量重新减为0并跳出阻塞状态。
 * 实际上就是通过这种特性完成临界区的同步操作，可以通过如下形式同步临界区（假设信号量的初始值为1）。
 */

void* read(void* arg);
void* accu(void* arg);

int main(int argc, char** argv)
{
    pthread_t id_t1, id_t2;
    sem_init(&m_sem, 0, 0);
    sem_init(&n_sem, 0, 1);

    pthread_create(&id_t1, NULL, read, NULL);
    pthread_create(&id_t2, NULL, accu, NULL);

    pthread_join(id_t1, NULL);
    pthread_join(id_t2, NULL);

    sem_destroy(&m_sem);
    sem_destroy(&n_sem);

    return 0;
}

void* read(void* arg)
{
    for(int i = 0; i < 5; i++)
    {
        fputs("Input num: ", stdout);
        sem_wait(&n_sem);
        std::cin >> num;
        sem_post(&m_sem);
    }

    return nullptr;
}

void* accu(void* arg)
{
    int sum = 0;
    for(int i = 0; i < 5; i++)
    {
        sem_wait(&m_sem);
        sum += num;
        sem_post(&n_sem);

    }
    std::cout << "sum = " << sum << std::endl;

    return nullptr;
}