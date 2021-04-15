#include "list.h"

List::List() : head(new LNode), len(0)
{
}

List::~List()
{
    LNode* p = head->next;
    LNode* temp;
    while(p != nullptr)
    {
        temp = p;
        p = p->next;
        delete temp;
    }
}

void List::init()
{
    for(int i = 0; i < 5; i++)
    {
        LNode* temp = new LNode;
        if(temp == nullptr)
        {
            delete head;
            delete temp;
            exit(0);
        }
        temp->data = i + 1;
        temp->next = nullptr;

        if(end == nullptr)
        {
            head = temp;
        } else
        {
            end->next = temp;
        }

        end = temp;
        len++;
    }
    end->next = nullptr;

}

void List::show()
{
    LNode* p = head;

    while(p != nullptr)
    {
        std::cout << p->data << " ";
        p = p->next;
    }

    std::cout << std::endl;
}

void List::Insert()
{
    const int num = 6;
    LNode* q = new LNode;
    q->data = num;
    q->next = nullptr;
    if(q == nullptr)
    {
        delete head;
        delete q;
        exit(0);
    }

    end->next = q;
    end = q;
    end->next = nullptr;
    len++;
}

void List::head_Insert()
{
    const int num2 = 0;
    LNode* q = new LNode;
    q->data = num2;
    q->next = head;
    head = q;
    len++;
}

void List::Delete()
{
    int index = 3;
    if(index > len)
    {
        index = index - len;
    }

    LNode* p = head;
    for(index; index > 1; index--)
    {
        p = p->next;
    }

    LNode* temp = p->next;
    p->next = temp->next;
    delete temp;
}