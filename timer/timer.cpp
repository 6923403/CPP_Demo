#include "timer.h"

Timer::Timer() : m_expired(true), m_try_to_expire(false)
{

}

Timer::~Timer()
{
    stop();
}

Timer::Timer(const Timer& timer)
{
    m_expired = timer.m_expired.load();
    m_try_to_expire = timer.m_try_to_expire.load();
}
