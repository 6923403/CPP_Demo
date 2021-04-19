#include "LStock.h"

LStock::LStock() : stock(new Stock)
{

}

LStock::~LStock()
{
    Stock* q = stock;
    Stock* temp;
    while(q->next != nullptr)
    {
        temp = q;
        q = q->next;
        delete temp;
    }
}

void LStock::push(int num)
{
    Stock* q = new Stock;
    q->data = num;
    q->next = stock;
    stock = q;
}

void LStock::pop()
{
    Stock* q = stock;
    std::cout << "pop: " << q->data << std::endl;
    stock = stock->next;
    delete q;
}

void LStock::show()
{
    Stock* q = stock;
    while(q->next != nullptr)
    {
        std::cout << q->data << " ";
        q = q->next;
    }
    std::cout << std::endl;
}

