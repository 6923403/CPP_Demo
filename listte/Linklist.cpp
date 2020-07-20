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
    Link *head, *p, *pre;
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
    Link * p;
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

void test3() //add list
{
    Link *list3 = creatlist();
    Link *head, *p;
    head = list3;
    p = head;

    for(int i = 0; i < 3; i++)
        p = p->next;
    Link * val = new Link;
    val->data = 51;
    val->next = p->next;
    p->next = val;
    

    Link *sh;
    sh = head;
    while(sh->next != NULL)
    {
        sh = sh->next;
        cout << sh->data << endl;
    }
}

int main(int argc, char **argv)
{
    test3();

    return 0;
}
