#include "screen.h"

Screen &Screen::move(int a, int b)
{
    pa = a;
    pb = b;
    return *this;
}

Screen &Screen::set(char c)
{
    contents[pa + pb] = c;
    cout << contents << endl;
    return *this;
}

Screen &Screen::set(int a, int b, char c)
{
    contents[a + b] = c;
    cout << contents << endl;
}

Screen &Screen::display(ostream &os)
{
    do_display(os);
    return *this;
}

const Screen &Screen::display(ostream &os) const
{
    do_display(os);
    return *this;
}

void Screen::do_display(ostream &os) const
{
    os << contents;
}
