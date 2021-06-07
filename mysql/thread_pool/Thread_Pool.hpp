#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <list>
#include <queue>
#include <exception>

#include "../log/easylogging.h"

template<typename T>
class Thread_Pool {
public:
    Thread_Pool(int actor, int thread_num, int max_request = 1000);
    ~Thread_Pool();

    int addTask();
    int add_thread();

public:
    static void *work();

private:
    int m_actor;
    int m_thread_num;
    int m_maxrequest;
    pthread_t *m_threads;

    std::vector<T* > threads;
    std::queue<T* > tasks;

};

template <typename T>
Thread_Pool<T>::Thread_Pool(int actor, int thread_num, int max_request) : m_actor(actor), m_thread_num(thread_num), m_maxrequest(max_request)
{
    if(m_thread_num <= 0 || m_maxrequest <= 0)
    {
        LOG(ERROR) << "thread_num || max_request <= 0";
        throw std::exception();
    }

    for(int i = 0; i < 5; i++)
    {
        m_threads = new pthread_t[m_thread_num];
        if(m_threads)
            break;
        else
            LOG(ERROR) << "thread new failed";
            if(i == 5)
            {
                throw std::exception();
            }
    }

}

template <typename T>
Thread_Pool<T>::~Thread_Pool()
{
    delete[] m_threads;
}

#endif //THREAD_POOL_H
