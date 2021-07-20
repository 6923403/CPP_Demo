#ifndef LOCKER_H
#define LOCKER_H

#include <pthread.h>
#include <exception>
#include <semaphore>

class Sem
{
public:
    Sem();
    ~Sem();

    bool Sem_wait();
    bool Sem_post();

private:
    sem_t m_sem;

};

class Locker {
public:
    Locker();
    ~Locker();

    bool Lock();
    bool unLock();

private:
    pthread_mutex_t m_mutex;

};

class Cond
{
public:
    Cond();
    ~Cond();

    bool Cond_wait();
    bool Cond_signal();

    bool Cond_lock();
    bool Cond_unlock();

private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;

};


#endif //LOCKER_H
