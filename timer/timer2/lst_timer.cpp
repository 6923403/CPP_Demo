#include "lst_timer.h"

util_timer::util_timer() : prev(nullptr), next(nullptr)
{

}

lst_timer::lst_timer() : head(nullptr), tail(nullptr)
{

}

lst_timer::~lst_timer()
{
    util_timer *tmp = head;
    while(tmp)
    {
        head = tmp->next;
        delete tmp;
        tmp = head;
    }
}

void lst_timer::add_timer(util_timer *timer)
{
    if(timer == nullptr)
    {
        return;
    }

    if(head == nullptr)
    {
        head = tail = timer;
        return;
    }

    if(timer->expire < head->head)
    {
        timer->next = head;
        head->prev = timer;
        head = timer;
        return;
    }

    add_timer(timer, head);
}

void add_timer(util_timer *timer, util_timer *head)
{
    util_timer *h_prev = head;
    util_timer *tmp = h_prev->next;

    while(tmp)
    {
        if(timer->expire < tmp->expire)
        {
            h_prev->next = timer;
            timer->next = tmp;
            tmp->prev = timer;
            timer->prev = h_prev;
            break;
        }

        h_prev = tmp;
        tmp = tmp->next;
    }
    if(tmp == nullptr)
    {
        h_prev->next = timer;
        timer->prev = h_prev;
        timer->next = nullptr;
        tail = timer;
    }

}

void lst_timer::adjust_tiimer(util_timer *timer)
{
    if(timer == nullptr)
        return;
    util_timer *tmp = timer->next;
    if(!tmp || (timer->expire < tmp->expire))
    {
        return;
    }

    /*
     * 如果目标定时器是链表的头节点,则将该定时器从链表中取出井重新插入链表
     */
    if(timer == head)
    {
        head = head->next;
        head->prev = nullptr;
        head->next = nullptr;
        add_timer(timer, head);
    }
    else
    {
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        add_timer(timer, head);
    }
}

void lst_timer::del_timer(util_timer *timer)
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
    else if(timer == head)
    {
        head = head->next;
        head->prev = nullptr;
        delete timer;
        return;
    }
    else if(timer == tail)
    {
        tail = tail->prev;
        tail->next = nullptr;
        delete tail;
        return;
    }
    else
    {
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        delete timer;
        return;
    }
}

class Utils;
void cb_func(client_data *user_data)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->sockfd, 0);
    assert(user_data);
    close(user_data->sockfd);
    http_conn::m_user_count--;
}

void lst_timer::tick()
{
    if(!head)
    {
        return;
    }
    std::cout << "timer tick " << std::endl;
    time_t cur = time(nullptr);
    util_timer *tmp = head;
    while(tmp)
    {
        if(cur < tmp->expire)
        {
            break;
        }
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


