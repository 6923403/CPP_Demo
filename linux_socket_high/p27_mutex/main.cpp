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
        sem_lock.wait();

        n = 1;
        fprintf(stderr, "other thread %d  n: %d\n", i, n);
        sem_lock.post();

        i--;
    }
}

void* result(void *arg)
{
    cond_lock.lock();
    cond_lock.wait();
    fprintf(stderr, "OK...\n");
    cond_lock.unlock();
}

int main(int argc, char **argv)
{
    pthread_t id1, id2;
    pthread_create(&id1, NULL, handler, NULL);
    pthread_create(&id2, NULL, result, NULL);

    int i = 10;
    while(i > 0)
    {
        m_sem.wait();

        n = 3;
        std::cout << "thread: " << i << " n = " << n << std::endl;
        i--;

        m_sem.Sem_post();
    }

    void *status;
    pthread_join(id1, &status);
    m_cond.signal();
    pthread_join(id2, &status);

    return 0;
}