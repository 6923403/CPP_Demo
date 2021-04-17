#ifndef CPP_DEMO_STOCK_H
#define CPP_DEMO_STOCK_H

#include <iostream>
#include <algorithm>

const int Max_size = 100;

struct S_Stock
{
    int* pbase;
    int* ptop;
    int st_size;
};

class Stock
{
public:
    Stock();
    ~Stock();

    void init();
    void push(int num);
    void pop();
    void get_top();
    void show();

private:
    Stock(const Stock& stock);
    S_Stock* stock;
};

#endif //CPP_DEMO_STOCK_H
