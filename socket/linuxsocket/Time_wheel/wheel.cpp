#ifndef TIME_WHEEL_TIMER
#define TIME_WHEEL_TIMER

#include <time.h>
#include <netinet/in.h>
#include <stdio.h>

const int BUFFER_SIZE = 64;

class tw_timer;

struct client_data
{
    sockaddr_in address;
    int sockfd;
    char buf[BUFFER_SIZE];
    tw_timer* timer;
};

class tw_timer
{
    public:
        tw_timer(int rot, int ts) : next(NULL), prev(NULL), rotation(rot), time_slot(ts) {}

    public:
        int rotation;
        int time_slot;
        void (*cb_func)(client_data *);
        client_data * user_data;

        tw_timer* next;
        tw_timer* prev;
};

class time_wheel
{
    public:
        time_wheel() : cur_slot(0)
        {
            for(int i = 0; i < N; ++i)
            {
                slots[i] == NULL;
            }
        }

        ~time_wheel()
        {
            for(int i = 0; i < N; ++i)
            {
                tw_timer* tmp = slots[i];
                while(tmp)
                {
                    slots[i] = tmp->next;
                    delete tmp;
                    tmp = slots[i];
                }
            }
        }

        tw_timer * add_timer(int timeout)
        {
            if(timeout < 0)
            {
                return NULL;
            }
            int ticks = 0;

            if(timeout < SI)
            {
                ticks = 1;
            }
            else
            {
                ticks = timeout / SI;
            }

            int rotation = ticks / N;
            int ts = (cur_slot + (ticks % N)) % N; //定时器插入哪个槽
            tw_timer* timer = new tw_timer(rotation, ts);

            if(!slots[ts])
            {
                std::cout << "当前无定时器...\n 插入新的定时器" << endl;
                slots[ts] = timer;
            }
            else
            {
                timer->next = slots[ts];
                slots[ts]->prev = timer;
                slots[ts] = timer;
            }

            return timer;
        }

        void del_timer(tw_timer* timer)
        {
            if(!timer)
            {
                return;
            }
            int ts = timer->time_slot;

            if(timer == slots[ts])
            {
                slots[ts] = slots[ts]->next;
                if(slots[ts])
                {
                    slots[ts]->prev = NULL;
                }
                delete timer;
            }
            else
            {
                timer->prev->next = timer->next;
                if(timer->next)
                {
                    timer->next->prev = timer->prev;
                }

                delete timer;
            }
        }

        void tick()
        {
            tw_timer * tmp = slots[cur_slot];
            std::cout << "current slog is: " << cur_slot << std::endl; 
            while(tmp)
            {
                std::cout << "tick the timer once" << std::endl;
                if(tmp->rotation > 0)
                {
                    tmp->rotation--;
                    tmp = tmp->next;
                }
                else
                {
                    tmp->cb_func(tmp->user_data);
                    if(tmp == slots[cur_slot])
                    {
                        std::cout << "delete header in cur_slot" << std::endl;
                        slots[cur_slot] = tmp->next;
                        delete tmp;

                        if(slots[cur_slot])
                        {
                            slots[cur_slot]->prev = NULL;
                        }

                        tmp = slots[cur_slot];
                    }
                    else
                    {
                        tmp->prev->next = tmp->next;
                        if(tmp->next)
                        {
                            tmp->next-prev = tmp->prev;
                        }
                        tw_timer * tmp2 = tmp->next;
                        delete tmp;
                        tmp = tmp2;
                    }
                }
            }
            cur_slot = ++cur_slot % N;
        }

    private:
        static const int N = 60;
        static const int SI = 1;
        tw_timer * slots[N];
        int cur_slot;
};

#endif
