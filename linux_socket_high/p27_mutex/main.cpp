#include <iostream>
#include <unistd.h>

#include "Locker.h"

static int n = 1;
static Sem m_sem;
static Cond m_cond;
static Locker lock;


void* handler(void *arg)
{
    int i = 10;
    while (i>0) {
        m_sem.Sem_wait();

        n = 1;
        std::cout << "other thread: " << i << " n = " << n << std::endl;
        m_sem.Sem_post();

        i--;
    }
}

void* result(void *arg)
{
    m_cond.Cond_lock();
    m_cond.Cond_wait();
    std::cout << "OK.." << std::endl;
    m_cond.Cond_unlock();
}

int main(int argc, char **argv)
{
    pthread_t id1, id2;
    pthread_create(&id1, NULL, handler, NULL);
    pthread_create(&id2, NULL, result, NULL);

    int i = 10;
    while(i > 0)
    {
        m_sem.Sem_wait();

        n = 3;
        std::cout << "thread: " << i << " n = " << n << std::endl;
        i--;

        m_sem.Sem_post();
    }


    void *status;
    pthread_join(id1, &status);
    m_cond.Cond_signal();
    pthread_join(id2, &status);

    return 0;
}