#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while(0);

static void* sig_thread(void* arg)
{
    sigset_t* set = (sigset_t*) arg;
    int s, sig;

    for(;;)
    {
        s = sigwait(set, &sig);
        std::cout << "sss" << std::endl;
        if(s != 0)
        {
            handle_error_en(s, "sigwait");
        }
        std::cout << "signal handling thread  got signal = " << sig << std::endl;
    }
}

int main(int argc, char** argv)
{
    pthread_t thread;
    sigset_t set;
    int s;

    /*
     * 设置信号掩码
     */
    sigemptyset(&set);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGUSR1);

    s = pthread_sigmask(SIG_BLOCK, &set, NULL);
    if(s != 0)
    {
        handle_error_en(s, "pthread_sigmask");
    }

    s = pthread_create(&thread, NULL, &sig_thread, (void* ) &set);
    if(s != 0)
    {
        handle_error_en(s, "pthread_create");
    }

    std::cout << "bbb" << std::endl;

    return 0;
}
