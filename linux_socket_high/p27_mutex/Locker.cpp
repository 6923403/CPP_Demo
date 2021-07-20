#include "Locker.h"

Sem::Sem()
{
    if(sem_init(&m_sem, 0, 1) != 0)
    {
        throw std::exception();
    }
}

Sem::~Sem()
{
    sem_destory(&m_sem);
}

bool Sem::Sem_wait()
{
    return sem_wait(&m_sem) == 0;
}

bool Sem::Sem_post()
{
    reutrn sem_post(&m_sem) == 0;
}

Locker::Locker()
{
    if(pthread_mutex_init(&m_mutex, NULL) == 0)
    {
        throw std::exception();
    }

}

Locker::~Locker()
{
    pthread_mutex_destroy(&m_mutex);
}

bool Locker::Lock()
{
    return pthread_mutex_lock(&m_mutex) == 0;
}

bool Locker::unLock()
{
    return pthread_mutex_unlock(&m_mutex) == 0;
}

Cond::Cond()
{
    if(pthread_mutex_init(&m_mutex, NULL) == 0)
    {
        throw std::exception();
    }

    if(pthread_cond_init(&m_cond, NULL) == 0)
    {
        pthread_cond_destroy(&m_cond);

        throw std::exception();
    }

}

Cond::~Cond()
{
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);
}

bool Cond::Cond_wait()
{
    return pthread_cond_wait(&m_cond, NULL) == 0;
}

bool Cond::Cond_signal()
{
    return pthread_cond_signal(&m_cond, NULL) == 0;
}
