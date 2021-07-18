#ifndef TW_TIMER_H
#define TW_TIMER_H

#include <iostream>
#include <time.h>
#include <netinet/in.h>

const int BUFFER_SIZE = 64;

class tw_timer;
struct client_data
{
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    tw_timer *timer;
};

class tw_timer {
public:
    tw_timer(int rot, int ts) : next(NULL), prev(NULL), rotation(rot), time_slot(ts) {}

public:
    int rotation; //定时器在时间轮上转多少圈后生效
    int time_slot; //定时器属于时间轮上的哪个槽
    void (*cb_func)(client_data*);
    client_data *user_data;

    tw_timer *prev;
    tw_timer *next;
};

class time_wheel
{
public:
    time_wheel();
    ~time_wheel();

    tw_timer* add_timer(int timeout); //根据定时值创建定时器，并插入合适的位置
    void del_timer(tw_timer *timer); //删除目标定时器
    void tick(); //时间到后调用该函数，时间轮向前滚动一个槽间隔

private:
    static const int N = 60; //时间轮上槽的数目
    static const int TI = 1; //槽间隔时间，即每1秒时间轮转动一次

    int cur_slot; //时间轮的当前槽
    tw_timer *slots[N]; //时间轮的槽，其中每个元素指向一个定时器链表
};

#endif //TW_TIMER_H
