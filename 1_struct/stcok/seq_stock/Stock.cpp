#include "Stock.h"

Stock::Stock() : stock(new S_Stock){

}


Stock::~Stock()
{
    delete stock->pbase;
    delete stock;
}

void Stock::init() {
    stock->pbase = new int[Max_size];
    if(!stock->pbase)
    {
        delete stock;
        exit(0);
    }

    stock->ptop = stock->pbase;
    stock->st_size = Max_size;
}

void Stock::push(int num)
{
    if(stock->ptop - stock->pbase == stock->st_size)
    {
        std::cout << "栈内存已满" << std::endl;
        return;
    }

    *(stock->ptop++) = num;
    stock->st_size++;
}

void Stock::pop()
{
    if(stock->ptop == stock->pbase)
    {
        std::cout << "空栈" << std::endl;
        return;
    }

    std::cout << "pop: " << *--stock->ptop << std::endl;
    stock->st_size--;
}

void Stock::get_top()
{
    if(stock->ptop == stock->pbase)
    {
        std::cout << "空栈" << std::endl;
        return;
    }

    std::cout << "get_top: " << *--stock->ptop << std::endl;
    stock->st_size--;
}

void Stock::show()
{
    S_Stock* tmp = new S_Stock;
    tmp->ptop = stock->ptop;
    tmp->pbase = stock->pbase;
    while(tmp->ptop != tmp->pbase)
    {
        std::cout << *(--tmp->ptop) << " ";
    }

    std::cout << std::endl;
}
