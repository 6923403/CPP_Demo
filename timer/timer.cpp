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

sort_timer_list::sort_timer_list() : head(nullptr), tail(nullptr)
{
}

sort_timer_list::~sort_timer_list()
{
    Timer* tmp = nullptr;
    tmp = head;

    while(tmp)
    {
        head = tmp->next;
        delete tmp;
        tmp = head;
    }
}

void sort_timer_list::add_timer(Timer* timer)
{
    if(!timer)
    {
        return;
    }

    if(!head)
    {
        head = tail = timer;
        return;
    }

    if(timer->expire < head->expire)
    {
        timer->next = head;
        head->prev = timer;
        head = timer;
        return;
    }

    add_timer(timer, head);
}

void sort_timer_list::adjust_timer(Timer* timer)
{
    if(!timer)
    {
        return;
    }

    Timer* tmp = nullptr;
    timer = tmp->timer->next;

    if(!timer || (timer->expire < tmp->expire))
    {
        return;
    }

    if(timer == head)
    {
        head = head->next;
        head->prev = nullptr;
        timer->next = nullptr;
        add_timer(timer, head);
    }
    else
    {
        /*
         * 如果不是链表头节点 则将该定时器从链表中取出 然后插入所在位置之后的部分链表中
         */
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        add_timer(timer, timer->next);
    }
}

void sort_timer_list::del_timer(Timer* timer)
{
    if(!timer)
    {
        return;
    }

    if((timer == head) && (timer == tail))
    {
        delete timer;
        head = nullptr;
        tail = nullptr;
        return;
    }

    if(timer == head)
    {
        head = head->next;
        head->prev = nullptr;
        delete timer;
        return;
    }

    if(timer == tail)
    {
        tail = tail->prev;
        tail->next = nullptr;
        delete timer;
        return;
    }

    timer->prev->next = timer->next;
    timer->next->prev = timer->prev;
    delete timer;
}

void sort_timer_list::tick()
{
    if(!head)
    {
        return;
    }

    std::cout << "timer tick " << std::endl;
    time_t cur = time(NULL);
    Timer* tmp = head;

    while(tmp)
    {
        if(cur < tmp->expire)
        {
            break;
        }

        /*
         * 调用定时器回调函数 以执行定时任务
         */
        tmp->cb_func(tmp->user_data);
        head = tmp->next;

        if(head)
        {
            head->prev = nullptr;
        }

        delete tmp;
        tmp = head;
    }
}


void sort_timer_list::add_timer(Timer* timer, Timer* head)
{
    sort_timer_list* prev = lst_head;
    sort_timer_list* tmp = prev->next;

    while(tmp)
    {
        if(timer->expire < tmp->expire)
        {
            prev->next = timer;
            timer->next = tmp;
            tmp->prev = timer;
            timer->prev = prev;
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    if(!tmp)
    {
        prev->next = timer;
        timer->prev = prev;
    }
}