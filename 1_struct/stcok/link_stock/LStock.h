#ifndef CPP_DEMO_LSTOCK_H
#define CPP_DEMO_LSTOCK_H

#include <iostream>

struct Stock
{
    int data;
    Stock* next;
};

class LStock {
public:
    LStock();
    ~LStock();

    void push(int num);
    void pop();
    void show();

private:
    Stock* stock;

};

#endif //CPP_DEMO_LSTOCK_H
