#ifndef LST_TIMER_H
#define LST_TIMER_H

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>

class util_timer;
const int BUF_SIZE = 100;
struct client_data
{
    sockaddr_in address;
    int sockfd;
    char buf[BUF_SIZE];
    util_tiimer *timer;
};

class util_timer {
public:
    util_timer();

public:
    void (* cb_func)(client_data *);

    client_data *user_data;
    time_t expire; //任务超时时间
    util_timer *head;
    util_timer *prev;
    util_timer *next;
};

class lst_timer
{
public:
    lst_timer();
    ~lst_timer();

    void add_timer(util_timer *timer);
    void adjust_tiimer(util_timer *timer);
    void del_timer(util_timer *timer);
    void tick();

private:
    void add_timer(util_timer *timer, util_timer *head);

    util_timer *head;
    util_timer *tail;
};

#endif //LST_TIMER_H
