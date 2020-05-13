#include "screen.h"

inline Screen &Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;
}

char Screen::get(pos r, pos c) const
{
    pos row = r * width;
    return contents[row + c];
}

void Screen::some_member() const
{
    ++access_ctr;
}

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r * width + col] = ch;
    return *this;
}

/*Screen &Screen::display(ostream &os)
{
    do_display(os);
    return *this;
}
*/

const Screen &display(ostream &os) 
{
    do_display(os);
    return *this;
}

void Screen::do_display(ostream &os) const
{
    os << contents;
}
