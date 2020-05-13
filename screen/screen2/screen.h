#ifndef SCREEN_H
#define SCREEN_H

#include <string>
using namespace std;

class Screen
{
    public:
        //typedef string::size_type pos;
        using pos = string::size_type;
        Screen() = default;

        Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht * wd, c){}

        char get() const
        {
            return contents[cursor];
        }

        void some_member() const;

        char get(pos ht, pos wd) const;
        Screen &move(pos r, pos c);
        Screen &set(char);
        Screen &set(pos, pos, char);
        //Screen &display(ostream &os);
        const Screen &display(ostream &os);

    private:
        mutable size_t access_ctr;
        pos cursor = 0;
        pos height = 0, width = 0;
        string contents;
        void do_display(ostream &) const;
};

#endif
