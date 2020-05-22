#ifndef MYTIME_H_
#define MYTIME_H_

#include <iostream>

class Time
{
    private:
        int hours;
        int minutes;
        
    public:
        Time();
        Time(int h, int m = 0);
        void addMin(int m);
        void addHr(int h);
        void Reset(int h = 0, int m = 0);
        //Time Sum(const Time &) const;
        void show() const;
        Time operator+(const Time & ) const;
};

#endif
