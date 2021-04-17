#include "dlist.h"

void test()
{
    Dlist list;
    list.init();
    list.insert(1);
    list.insert(2);
    list.insert(4);
    list.insert(5);
    list.show();

    list.insert(3, 3);
    list.show();

    list.del_list(3);
    list.show();
}

int main()
{
    test();

    return 0;
}