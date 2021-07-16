#include "lst_timer.h"

sort_timer_lst::~sort_timer_lst()
{
    util_timer *tmp = head;

    while(tmp)
    {
        head = tmp->next;
        delete tmp;
        tmp = head;
    }
}

void sort_timer_lst::add_timer(util_timer *timer)
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

void sort_timer_lst::add_timer(util_timer *timer, util_timer *head)
{
    util_timer *prev = head;
    util_timer *tmp = prev->next;

    while(tmp)
    {
        if(timer->expire < tmp->expire)
        {
            prev->next = timer;
            timer->next = tmp;
            tmp->prev = timer;
            timer->prev = prev;
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    //无位置
    {
        prev->next = timer;
        timer->prev = prev;
        timer->next = nullptr;
        tail = timer;
    }
}

void sort_timer_lst::adjust_timer(util_timer *timer)
{
    if(!timer)
    {
        return;
    }

    util_timer *tmp = timer->next;
    if(!tmp || timer->expire < tmp->expire)
    {
        return;
    }

    //如果是头部，则取出并重新插入
    if(timer == head)
    {
        head = head->next;
        head->prev = nullptr;
        timer->next = nullptr;
        add_timer(timer, head);
    }
    else
    {
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        add_timer(timer, timer->next);
    }
}

void sort_timer_lst::del_timer(util_timer *timer)
{
    if(!timer)
    {
        return;
    }

    if(timer == head && timer == tail)
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

void sort_timer_lst::tick()
{
    if(head == nullptr)
    {
        return;
    }

    std::cout << "timer tick" << std::endl;
    time_t cur = time(NULL);
    util_timer *tmp = head;

    while(tmp)
    {
        if(cur < tmp->expire)
        {
            break;
        }

        tmp->cb_func(tmp->user_data);
        head = tmp->next;
        if (head)
            head->prev = NULL;

        delete tmp;
        tmp = head;
    }
}