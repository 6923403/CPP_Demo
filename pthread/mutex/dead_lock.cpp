#include <pthread.h>
#include <unistd.h>
#include <iostream>

int a = 0;
int b = 0;
pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;

void*  another(void* arg)
{
    pthread_mutex_lock(&mutex_b);
    std::cout << "another " << std::endl;

    sleep(3);
    ++b;

    pthread_mutex_lock(&mutex_a); //二次锁定 导致死锁
    b += a++;
    pthread_mutex_unlock(&mutex_a);
    pthread_mutex_unlock(&mutex_b);

    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t id;

    pthread_mutex_init(&mutex_a, NULL);
    pthread_mutex_init(&mutex_b, NULL);
    pthread_create(&id, NULL, another, NULL);

    pthread_mutex_lock(&mutex_a);

    std::cout << "start " << std::endl;
    sleep(3);

    ++a;
    pthread_mutex_lock(&mutex_b);
    a += b++;

    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);

    pthread_join(id, NULL);
    pthread_mutex_destroy(&mutex_a);
    pthread_mutex_destroy(&mutex_b);

    return 0;
}

