#include "locker.h"

Sem::Sem()
{
    if(sem_init(&m_sem, 0, 0) != 0)
    {
        throw std::exception();
    }
}

Sem::~Sem()
{
    sem_destroy(&m_sem);
}

bool Sem::wait()
{
    return sem_wait(&m_sem) == 0;
}

bool Sem::post()
{
    return sem_post(&m_sem) == 0;
}

/*
 * class Locker
 */

Locker::Locker()
{
    if(pthread_mutex_init(&m_mutex, NULL) != 0)
    {
        throw std::exception();
    }
}

Locker::~Locker()
{
    pthread_mutex_destroy(&m_mutex);
}

bool Locker::lock()
{
    return pthread_mutex_lock(&m_mutex) == 0;
}

bool Locker::unlock()
{
    return pthread_mutex_unlock(&m_mutex) == 0;
}

/*
 * class Cond
 */

Cond::Cond()
{
    if(pthread_mutex_init(&m_mutex, NULL) != 0)
    {
        throw std::exception();
    }
    if(pthread_cond_init(&m_cond, NULL) != 0)
    {
        throw std::exception();
    }
}

Cond::~Cond()
{
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);
}

bool Cond::wait()
{
    int ret;
    pthread_mutex_lock(&m_mutex);
    ret = pthread_cond_wait(&m_cond, &m_mutex);
    pthread_mutex_unlock(&m_mutex);
    return ret == 0;
}

bool Cond::signal()
{
    return pthread_cond_signal(&m_cond) == 0;
}
