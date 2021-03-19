#include "pool.h"

Pool::Pool()
{
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond, NULL);
    destroy_all = false;
}

Pool::~Pool()
{
    destroy_pool();
}

void Pool::init(int max_thread_num)
{
    std::cout << max_thread_num << std::endl;
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
    }
}

void Pool::add_pool(Task* work)
{
    pthread_mutex_lock(&m_mutex);
    Task_pool.push_back(work);
    pthread_cond_signal(&m_cond);
    pthread_mutex_unlock(&m_mutex);
}

void* Pool::worker(void *arg)
{
    if(arg == nullptr)
    {
        std::cout << "arg == null" << std::endl;
        exit(-1);
    }

    Pool* pool = (Pool *)arg;
    pool->run();
    return pool;
}

void Pool::run()
{
    Task* task = nullptr;
    pthread_mutex_lock(&m_mutex);

    while (true)
    {
        if(Task_pool.empty())
        {
            pthread_cond_wait(&m_cond, &m_mutex);
        }

        task = Task_pool.front();
        Task_pool.pop_front();
        pthread_mutex_unlock(&m_mutex);
        if(task == nullptr)
        {
            std::cout << "run() task == null " << std::endl;
            exit(-1);
        }

        task->run();

        // 线程池销毁判断，收到销毁信息退出线程
        if (destroy_all && Task_pool.empty())
        {
            std::cout << "Thread exited" << std::endl;
            pthread_exit(NULL);
            break;
        }

    }
}

void Pool::destroy_pool()
{
    if(!destroy_all)
    {
        std::cout << "destroy_pool " << std::endl;
        pthread_cond_broadcast(&m_cond);
        destroy_all = true;

        for(int i = 0; i < sizeof(m_threads); i++)
        {
            if(pthread_join(m_threads[i], NULL) != 0)
            {
                std::cout << "pthread_join error" << std::endl;
                delete[] m_threads;
                exit(-1);
            }
        }

        delete[] m_threads;
        pthread_cond_destroy(&m_cond);
        pthread_mutex_destroy(&m_mutex);
    }
}

bool Pool::back_destroy()
{
    return destroy_all;
}

Task::Task()
{
    i = 0;
}

Task::~Task()
{}

void Task::run()
{
    std::cout << "i = " << i++ << std::endl;
}