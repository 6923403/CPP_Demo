#ifndef CPP_DEMO_POOL_H
#define CPP_DEMO_POOL_H

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <list>
#include <vector>

class Task;

class Pool {
public:
    Pool();
    ~Pool();
    void init(int max_thread_num = 5);
    void add_pool();
    void destroy_pool();

    static void* worker(void* arg);

private:
    void run();
    int m_thread_num;

    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
    pthread_t* m_threads;

    std::list<Task*> Task_pool;
};

class Task {
public:
    Task();
    ~Task();

private:

};

#endif //CPP_DEMO_POOL_H
