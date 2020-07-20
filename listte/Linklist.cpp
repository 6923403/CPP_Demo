#include <iostream>
#include <stdlib.h>
using namespace std;

typedef int Status;
typedef int ElemType;

#define Len 5

class Link
{
    public:
        ElemType data;
        Link * next;
        Link * Node;
} *Linklist;

Link * creatlist()
{
    Link *head, *q, *p, *pre;
    head = new Link;
    head->next = nullptr;
    pre = head;

    for(int i = 0; i < 5; i++)
    {
        p = new Link;
        p->data = i;
        p->next = nullptr;
        pre->next = p;
        pre = p;
    }

    return head;
}

int searchlist(Link * head, int a)
{
    Link * q, * p;
    p = head->next;

    int num = 0;
    while(p != NULL)
    {
        if(p->data == a)
            return num;
        num++;
        p = p->next;
    }

    cout << "NUll data same" << endl;
}

void test1()
{
    //create list
    Link *list = creatlist();
    list = list->next;

    while(list != nullptr)
    {
        cout << "List " << list->data << endl;
        list = list->next;
    }
}

void test2()
{
    Link *list2 = creatlist();
    //search list
    int a = 3;
    int aa = searchlist(list2, a);
    cout << aa << endl;
}

int main(int argc, char **argv)
{
    test2();

    return 0;
}
