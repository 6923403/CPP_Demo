#ifndef LST_TIMER_H
#define LST_TIMER_H

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 64;

class util_timer;
struct client_data
{
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    util_timer *timer;
};

class util_timer
{
public:
    util_timer() : prev(nullptr), next(nullptr)
    {}

    time_t expire;
    void (*cb_func) (client_data *);
    client_data *user_data;
    util_timer *prev;
    util_timer *next;
};

class sort_timer_lst
{
public:
    sort_timer_lst() : head(nullptr), tail(nullptr)
    {}
    ~sort_timer_lst();

    void add_timer(util_timer *timer);
    void adjust_timer(util_timer *timer);
    void del_timer(util_timer *timer);

    //SIGALRM信号每次被触发时，就在其信号处理函数中执行一次（如果使用统一事件源，则是主函数），
    //以处理链表上到期的任务
    void tick();

private:
    void add_timer(util_timer *timer, util_timer *lst_head);

    util_timer *head;
    util_timer *tail;

};

#endif //LST_TIMER_H
