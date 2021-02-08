#ifndef CPP_DEMO_TIMER_LIST_H
#define CPP_DEMO_TIMER_LIST_H

#include <time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
const int BUFFER_SIZE = 1024;
class util_timer;

struct client_data
{
    sockaddr_in addr;
    int sockfd;
    char buf[BUFFER_SIZE];
    util_timer* timer;
};

class util_timer
{
public:
    util_timer() : prev(nullptr), next(nullptr)
    {

    }

private:
    void (*cb_func)(client_data* ); //任务回调函数
    time_t expire;
    client_data user_data;
    util_timer* prev;
    util_timer* next;
};

//定时器链表 升序双向
class sort_timer_list
{
public:
    sort_timer_list() : head(nullptr), tail(nullptr)
    {

    }

    ~sort_timer_list()
    {
        util_timer* tmp = nullptr;
        tmp = head;

        while(tmp != nullptr)
        {
            head = tmp->next;
            delete tmp;
            tmp = head;
        }
    }

    //定时器添加到链表
    void addTimer(util_timer* timer)
    {
        if(!timer)
        {
            return;
        }

        if(!head)
        {
            head = tail = timer;
        }

        /* 如果目标定时器的超时时间小于当前链表中所有定时器的超时时间，
         * 则把该定时器插入链表头部，作为链表新的头节点。
         * 否则就需要调用重载函数add_timer（util_timer*timer，util_timer*lst_head），
         * 把它插入链表中合适的位置，以保证链表的升序特性
         */
        if(timer->expire < head->expire)
        {
            timer->next = head;
            head->prev = timer;
            head = timer;
            return;
        }
        addTimer(timer, head);
    }

    /* 当某个定时任务发生变化时，调整对应的定时器在链表中的位置。
     * 这个函数只考虑被调整的定时器的超时时间延长的情况，
     * 即该定时器需要往链表的尾部移动
     */
    void adjust_timer(util_timer* timer)
    {
        if(!timer)
        {
            return;
        }
        util_timer* tmp = timer->next;

        /* 如果被调整的目标定时器处在链表尾部，
         * 或者该定时器新的超时值仍然小于其下一个定时器的超时值，
         * 则不用调整
         */
        if(!tmp || (timer->expire < tmp->expire))
        {
            return;
        }

        /* 如果目标定时器是链表的头节点，
         * 则将该定时器从链表中取出井重新插入链表
         */
        if(timer == head)
        {
            head = head->next;
            head->prev = nullptr;
            timer->next = nullptr;
            addTimer(timer, head);
        }
        /* 如果被调整的目标定时器处在链表尾部，
         * 或者该定时器新的超时值仍然小于其下一个定时器的超时值，
         * 则不用调整
         */
        else
        {
            timer->prev->next = timer->next;
            timer->next->prev = timer->prev;
            addTimer(timer, timer->next);
        }
    }

    /*
     * 将目标定时器 timer 从链表中删除
     */
    void delTimer(util_timer* timer) {
        if (timer == nullptr)
            return;

        /*
         * 下面这个条件成立表示链表中只有一个定时器,
         * 即目标定时器
         */
        if ((timer == head) && (timer == tail)) {
            delete timer;
            head = nullptr;
            tail = nullptr;
            return;
        }

        /*
         * 如果链表中至少有两个定时器，
         * 且目标定时器是链表的头结点，
         * 则将链表的头结点重置为原头节点的下一个节点，
         * 然后删除目标定时器
         */
        if (timer == head) {
            head = head->next;
            head->prev = nullptr;
            delete timer;
            return;
        }

        /*
         * 如果链表中至少有两个定时器，
         * 且目标定时器是链表的尾结点，
         * 则将链表的尾结点重置为原尾节点的前一个节点，
         * 然后删除目标定时器
         */
        if (timer == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            delete timer;
            return;
        }

        /*
         * 如果目标定时器位于链表的中间，
         * 则把它前后的定时器串联起来，
         * 然后删除目标定时器
         */
        timer->prev->next = timer->next;
        timer->next->prev = timer->prev;
        delete timer;
    }

    /*
     * 如果链表中至少有两个定时器，
     * 且目标定时器是链表的尾结点，
     * 则将链表的尾结点重置为原尾节点的前一个节点，
     * 然后删除目标定时器
     */
    void tick()
    {
        if(!head)
        {
            return;
        }
#include <iostream>
        std::cout << "timer tick" << std::endl;
        time_t cur = time(nullptr); //获取当前时间
        util_timer* tmp = head;
        /*
         * 从头结点开始依次处理每个定时器，
         * 直到遇到一个尚未到期的定时器，
         * 这就是定时器的核心逻辑
         */
        while (tmp)
        {
            /*
             * 因为每个定时器都使用绝对时间作为超时值，
             * 所以我们可以把定时器的超时值和系统当前时间，
             * 比较以判断定时器是否到期
             */
            if(cur < tmp->expire)
            {
                break;
            }
            /*
             * 调用定时器的回调函数，
             * 以执行定时任务
             */
            tmp->cb_func(tmp->user_data);

            /*
             * 执行完定时器中的定时任务之后，
             * 就将它从链表中删除，并重置链表头结点
             */
            head = tmp->next;
            if(head)
            {
                head->prev = nullptr;
            }
            delete tmp;
            tmp = head;
        }
    }

private:
    /* 一个重载的辅助函数，它被公有的 add_timer 函数和adjust_timer 函数调用。
     * 该函数表示将目标定时器 timer 添加到节点 lst_head之后的部分链表中
     */
    void addTimer(util_timer* timer, util_timer* lst_head)
    {
        util_timer* prev = lst_head;
        util_timer* tmp = prev->next;

        /* 遍历lst_head节点之后的部分链表，
         * 直到找到一个超时时间大于目标定时器的超时时间的节点，
         * 并将目标定时器插入该节点之前
         */
        while(tmp != nullptr)
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
            tmp = prev->next;
        }

        /* 如果遍历完 lst_head 节点之后的部分链表，
         * 仍未找到超时时间大于目标定时器的超时时间的节点，
         * 则将目标定时器插入链表尾部，
         * 并把它设置为链表新的尾节点
         */
        if(!tmp)
        {
            prev->next = timer;
            timer->prev = prev;
            prev->next = nullptr;
            tail = timer;
        }

    }

private:
    util_timer* head;
    util_timer* tail;
};

#endif //CPP_DEMO_TIMER_LIST_H
