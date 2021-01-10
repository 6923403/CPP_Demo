#ifndef CPP_DEMO_LOCKER_H
#define CPP_DEMO_LOCKER_H

#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

class Locker
{
public:
    Locker();
    ~Locker();
    bool lock();
    bool unlock();

private:
    pthread_mutex_t m_mutex;
};

class Sem
{
public:
    Sem();
    ~Sem();
    bool wait();
    bool post();

private:
    sem_t m_sem;
};

class Cond
{
public:
    Cond();
    ~Cond();
    bool wait();
    bool signal();

private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

#endif //CPP_DEMO_LOCKER_H
