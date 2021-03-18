#ifndef CPP_DEMO_POOL_H
#define CPP_DEMO_POOL_H

/*
 * https://zhuanlan.zhihu.com/p/321319234
 * https://zhuanlan.zhihu.com/p/88896082
 */

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <list>
#include <vector>

class Task;

class Pool {
public:
    Pool();
    virtual ~Pool();
    void init(int max_thread_num = 5);
    void add_pool(Task* work);
    void destroy_pool();
    bool back_destroy();

    static void* worker(void* arg);

private:
    void run();
    int m_thread_num;

    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
    pthread_t* m_threads;

    std::list<Task*> Task_pool;
    bool destroy_all;
};

class Task {
public:
    Task();
    ~Task();

    void run();

private:
    int i;

};

#endif //CPP_DEMO_POOL_H
