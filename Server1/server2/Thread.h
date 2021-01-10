#ifndef CPP_DEMO_THREAD_H
#define CPP_DEMO_THREAD_H

#include <unistd.h>
#include <iostream>
#include <list>
#include <exception>

#include "locker.h"
#include "Http.h"

template <typename T>
class Thread_pool
{
public:
    Thread_pool();
    ~Thread_pool();
    bool addjob(T* request);

private:
    static void* worker(void* arg);
    void run();

    int max_thread;
    int max_job;
    pthread_t* pthread_pool;
    std::list<T> m_worker_queue;
    Locker m_queue_locker;
    Sem m_queue_stat;
    bool m_stop;

};

template <typename T>
Thread_pool<T>::Thread_pool()
{
    max_job = 1000;
    max_thread = 8;
    m_stop = false;
    pthread_pool = new pthread_t[max_thread];
    if(!pthread_pool)
    {
        throw std::exception();
    }

    for(int i = 0; i < max_thread; i++)
    {
        std::cout << "Create Pthread: " << i << std::endl;
        if(pthread_create(pthread_pool + i, NULL, worker, this) != 0)
        {
            delete[] pthread_pool;
            throw std::exception();
        }
        /*
         * 将线程分离
         */
        if(pthread_detach(pthread_pool[i]) != 0)
        {
            delete[] pthread_pool;
            throw std::exception();
        }
    }
}

template <typename T>
Thread_pool<T>::~Thread_pool()
{
    delete[] pthread_pool;
    m_stop = true;
}

template <typename T>
bool Thread_pool<T>::addjob(T *request)
{
    m_queue_locker.lock();
    if(m_worker_queue.size() > max_job)
    {
        m_queue_locker.unlock();
        return false;
    }
    m_worker_queue.push_back(request);
    m_queue_locker.unlock();
    m_queue_stat.post();
    return true;
}

template <typename T>
void* Thread_pool<T>::worker(void* arg)
{
    Thread_pool* pool = (Thread_pool* ) arg;
    pool->run();
    return pool;
}

template <typename T>
void Thread_pool<T>::run()
{
    while(!m_stop)
    {
        m_queue_stat.wait(); //信号量减1，直到为0的时候线程挂起等待
        m_queue_locker.lock();
        if(m_worker_queue.empty())
        {
            m_queue_locker.unlock();
            continue;
        }
        T* request = m_worker_queue.front();
        m_worker_queue.pop_front();
        m_queue_locker.unlock();
        if(!request)
        {
            continue;
        }
        request->doit();
    }
}

#endif //CPP_DEMO_THREAD_H
