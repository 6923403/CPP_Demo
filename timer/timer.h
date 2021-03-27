#ifndef CPP_DEMO_TIMER_H
#define CPP_DEMO_TIMER_H

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>

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
