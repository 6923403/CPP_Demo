#ifndef CPP_DEMO_TIMER_H
#define CPP_DEMO_TIMER_H

#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>

//https://blog.csdn.net/zhizhengguan/article/details/107313758
//https://blog.csdn.net/zang141588761/article/details/85600194
//https://blog.csdn.net/u012234115/article/details/89857431

const int BUFFER_SIZE = 64;

class Timer;

struct client_data
{
    sockaddr_in addr;
    int sockfd;
    char buf[BUFFER_SIZE];
    Timer* timer;
};

class Timer {
public:
    Timer();
    Timer(const Timer& timer);
    ~Timer();

public:
    void (*cb_func)(client_data*);

    client_data* user_data;
    time_t expire; //超时时间
    Timer* prev;
    Timer* next;

private:
    std::mutex m_mutex;

    bool m_expired;
    bool m_try_to_expire;
};

class sort_timer_list
{
public:
    sort_timer_list();
    ~sort_timer_list();

    void add_timer(Timer* timer);
    void adjust_timer(Timer* timer);
    void del_timer(Timer* timer);
    void tick();

public:
    void add_timer(Timer* timer, Timer* head);

    sort_timer_list* head;
    sort_timer_list* tail;

private:

};

#endif //CPP_DEMO_TIMER_H
