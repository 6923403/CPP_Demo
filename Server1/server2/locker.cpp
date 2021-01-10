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
 * --Locker
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
