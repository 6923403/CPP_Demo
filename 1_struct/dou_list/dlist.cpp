#include "dlist.h"

Dlist::Dlist() : list(new DNode)
{

}

Dlist::~Dlist()
{
    delete list;
}

void Dlist::init()
{
    if(list == nullptr)
    {
        std::cout << "new 出错" << std::endl;
        exit(0);
    }
    list->next = nullptr;
    list->prev = nullptr;
    list->data = 0;

    end = list;
}

void Dlist::insert(int num)
{
    DNode* p = new DNode;
    if(p == nullptr)
    {
        std::cout << "p error" << std::endl;
        delete p;
        exit(0);
    }

    p->data = num;
    if(list->next == nullptr)
    {
        p->prev = list;
        p->next = nullptr;
        list->next = p;
    }
    else
    {
        end->next = p;
        p->prev = end;
        p->next = nullptr;
    }

    end = p;
}

void Dlist::insert(int num, int index)
{
    DNode* p = list->next;
    for(int i = 1; i < index - 1; i++)
    {
        p = p->next;
    }

    DNode* q = new DNode;
    q->data = num;
    q->prev = p;
    q->next = p->next;
    p->next->prev = q;
    p->next = q;
}

void Dlist::del_list(int index)
{
    DNode* p = list->next;
    for(int i = 1; i < index - 1; i++)
    {
        p = p->next;
    }

    DNode* temp = p->next;
    temp->next->prev = p;
    p->next = p->next->next;
    delete temp;
}

void Dlist::show()
{
    DNode* p = nullptr;
    p = list->next;
    while(p != nullptr)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}