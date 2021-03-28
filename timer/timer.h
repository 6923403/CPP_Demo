#ifndef CPP_DEMO_TIMER_H
#define CPP_DEMO_TIMER_H

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

class Timer {
public:
    Timer();
    Timer(const Timer& timer);
    ~Timer();

private:
    std::mutex m_mutex;

    bool m_expired;
    bool m_try_to_expire;
};


#endif //CPP_DEMO_TIMER_H
