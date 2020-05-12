#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>
using namespace std;

class Screen
{
    public:
        Screen(){}

        Screen(int a, int b, char c):pa(a), pb(b), cc(c)
        {
            contents[pa + pb] = cc;
        }

        Screen &move(int , int);
        Screen &set(char);
        Screen &set(int, int, char);
        Screen &display(ostream &);
        const Screen &display(ostream &) const;

    private:
        void do_display(ostream &) const;

        int pa;
        int pb;
        char cc;
        string contents;
};

#endif
