#include "Stock.h"

void test()
{
    Stock s;
    s.init();
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.show();
    s.get_top();
    s.pop();
}

int main()
{
    test();
    std::cout << "done" << std::endl;
    return 0;
}