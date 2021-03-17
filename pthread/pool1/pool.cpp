#include "pool.h"

Pool::Pool()
{
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond, NULL);
}

Pool::~Pool() {

}

void Pool::init(int max_thread_num)
{
    int ret;
    m_threads = new pthread_t[max_thread_num];
    m_thread_num = max_thread_num;
    if(!m_threads)
    {
        std::cout << "m_threads == null" << std::endl;
        exit(-1);
    }

    for(int i = 0; i < m_thread_num; i++)
    {
        if(pthread_create(&m_threads[i], NULL, worker, (void *)this) != 0)
        {
            std::cout << "pthread_create error" << std::endl;
            delete[] m_threads;
            exit(-1);
        }

        if(pthread_join(m_threads[i], NULL) != 0)
        {
            std::cout << "pthread_join error" << std::endl;
            delete[] m_threads;
            exit(-1);
        }
    }
    std::cout << "pool init1" << std::endl;
}

void* Pool::worker(void *arg)
{
    std::cout << "pool init2" << std::endl;
    if(arg == nullptr)
    {
        std::cout << "arg == null" << std::endl;
        exit(-1);
    }

    Pool* pool = (Pool *)arg;
    pool->run();
}

void Pool::run()
{
    std::cout << "pool init3" << std::endl;
    Task* task = nullptr;
    pthread_mutex_lock(&m_mutex);
    std::cout << "pool init4" << std::endl;

    while (true)
    {
        if(Task_pool.empty())
        {
            std::cout << "pool init5" << std::endl;
            pthread_cond_wait(&m_cond, &m_mutex);
        }

        std::cout << "pool init6" << std::endl;

        Task* task = Task_pool.front();
        Task_pool.pop_front();
        pthread_mutex_unlock(&m_mutex);
        if(task == nullptr)
        {
            std::cout << "run() task == null " << std::endl;
            exit(-1);
        }

    }
}
