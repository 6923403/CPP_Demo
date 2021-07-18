#include "tw_timer.h"

time_wheel::time_wheel():cur_slot(0)
{
    //初始化每个槽的头结点
    for (int i = 0; i < N; ++i)
        slots[i] = NULL;
}

time_wheel::~time_wheel()
{
    //遍历每个槽，并销毁定时器
    for (int i = 0; i < N; ++i) {
        tw_timer *tmp = slots[i];
        while (tmp) {
            slots[i] = tmp->next;
            delete tmp;
            tmp = slots[i];
        }
    }
}

tw_timer* time_wheel::add_timer(int timeout)
{
    if (timeout < 0)
        return NULL;

    int ticks = 0;              //待插入定时器所需要总ticks
    if (timeout < TI)
        ticks = 1;
    else
        ticks = timeout / TI;

    int rotation = ticks / N;   //计算待插入的定时器在时间轮上要转动多少圈后触发
    int ts = (cur_slot + ticks) % N; //计算待持入定时器应该被插入的位置
    //int ts = (cur_slot + (ticks %N)) % N;

    //创建定时器，它在时间轮转动rotation圈之后触发，且位于第ts个槽上
    tw_timer *timer = new tw_timer(rotation, ts);

    //如果槽为空，则它新定时器插入，并设置为该槽的头节点
    if (!slots[ts]) {
        std::cout << "add timer, rotation is: " << rotation << " ts is: " << ts <<  "cur_slot is: " << cur_slot << std::endl;
        slots[ts] = timer;
    }
    else {
        timer->next = slots[ts];
        slots[ts]->prev = timer;
        slots[ts] = timer;
    }

    return timer;
}

void time_wheel::del_timer(tw_timer *timer)
{
    if (!timer)
        return;

    int ts = timer->time_slot;
    if (timer == slots[ts]) {   //如果是头结点
        slots[ts] = slots[ts]->next;
        if (slots[ts])
            slots[ts]->prev = NULL;

        delete timer;
    }
    else {
        timer->prev->next = timer->next;
        if (timer->next)
            timer->next->prev = timer->prev;

        delete timer;
    }
}

void time_wheel::tick()
{
    //取得时间轮上当前槽的头结点
    tw_timer *tmp = slots[cur_slot];
    printf("current slot is %d\n", cur_slot);

    while (tmp) {
        printf("tick the timer once\n");

        //如果定时器的rotation值大于0，则未到时，不处理
        if (tmp->rotation > 0) {
            tmp->rotation--;
            tmp = tmp->next;
        }
        else {
            tmp->cb_func(tmp->user_data);
            if (tmp == slots[cur_slot]) {
                printf("delete header in cur_slot\n");
                slots[cur_slot] = tmp->next;

                delete tmp;

                if (slots[cur_slot])
                    slots[cur_slot]->prev = NULL;

                tmp = slots[cur_slot];
            }
            else {
                tmp->prev->next = tmp->next;
                if (tmp->next)
                    tmp->next->prev = tmp->prev;

                tw_timer *tmp2 = tmp->next;

                delete tmp;
                tmp = tmp2;
            }
        }
    }

    //更新时间轮的当前槽，以反映时间轮的转动
    cur_slot = ++cur_slot % N;
}


