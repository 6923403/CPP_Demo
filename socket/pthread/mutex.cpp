#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

const int Thread_num = 10;

void* thread_inc(void* arg);
void* thread_des(void* arg);

long long num = 0;
long long num2 = 0;
pthread_mutex_t m_mutex;

int main(int argc, char** argv)
{
    pthread_t thread_id[Thread_num];
    pthread_mutex_init(&m_mutex, NULL);

    for(int i = 0; i < Thread_num; i++)
    {
       if(i % 2)
       {
           pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
       }
       else
       {
           pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
       }

    }

    for(int k = 0; k < Thread_num; k++)
    {
        pthread_join(thread_id[k], NULL);
    }

    std::cout << "result = " << num << std::endl;
    std::cout << "result2 = " << num2 << std::endl;

    pthread_mutex_destroy(&m_mutex);
    return 0;
}

void* thread_inc(void* arg)
{
    int i = 0;
    pthread_mutex_lock(&m_mutex);
    for(i = 0; i < 10; i++)
    {
        num += 1;
    }

    pthread_mutex_unlock(&m_mutex);
    return nullptr;
}

void* thread_des(void* arg)
{
    int k = 0;
    pthread_mutex_unlock(&m_mutex);
    for(k = 0; k < 10; k++)
    {
        num2 += 1;
    }
    pthread_mutex_unlock(&m_mutex);

    return nullptr;
}