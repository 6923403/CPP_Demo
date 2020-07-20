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
}* Linklist;

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

    int num;
    while(p != NULL)
    {
        if(p->data == a)
            num++;
        p = p->next;
    }
}

int main(int argc, char **argv)
{
    //create list
    Link *list = creatlist();
    list = list->next;

    while(list != nullptr)
    {
        cout << "List " << list->data << endl;
        list = list->next;
    }

    //search list
    int a = 3;
    searchlist(list, a);

    return 0;
}
