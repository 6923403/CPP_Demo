#include <cstring>
#include <iostream>
#include <cstdlib>

typedef struct Linklist
{
    int data;
    Linklist* next;
}List;

void show(List* list)
{
    List* p = list;
    while(p)
    {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

List* init(List* list)
{
    List* p, *q;
    p = list;
    for(int i = 0; i < 8; i++)
    {
        q = new Linklist;
        if(q == nullptr)
        {
            return list;
        }

        q->data = i + 1;
        q->next = nullptr;
        if(p == nullptr)
        {
            list = q;
        }
        else p->next = q;
        p = q;
    }

    delete q;
    return list;
}

void Insert(List* list)
{
    const int num = 9;
    List* p, *q;
    q = new List;
    q->data = num;
    q->next = p->next;
    if(list == nullptr) {
        list = q;
        return list;
    }
    p = list;

    while(p != nullptr)
    {
        p = p->next;
    }

    p = q;

}

void test1()
{
    List* list = nullptr;
    list = init(list);
    show(list);

    Insert(list);
    show(list);
}

int main(int argc, char** argv)
{
    test1();
    return 0;
}