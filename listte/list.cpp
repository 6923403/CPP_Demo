#include <iostream>
using namespace std;

void te1();
void te2();

class List
{
    public:
        int m_key;
        int data;
        List * node;
        List * next;
};

List createList(List *phead)
{
    for(int i = 1; i< 5; i++)
    {
        List *pNewNode = new List;
        pNewNode->m_key = i;
        pNewNode->next = nullptr;
        phead->next = nullptr;
        phead = pNewNode;
    }
    return *phead;

}

int main(int argc, char **argv)
{
    te2();
}

List * creat()
{
    List * head;
    List * p;
    List * q;

    head = new List;
    p = head;

    for(int i = 0; i < 5; i++)
    {
        q = new List;
        q->data = i;
        cout << "q->data: " << q->data << endl;

        p->next = q;
        p = q;
    }
    head = head->next;
    p->next = nullptr;
    cout << "head->data: " << head->data << endl;
    return head;
}

void te2()
{
    List * ls = creat();
    cout << "ls->data: " << ls->data << endl;
}

void te1()
{
    List * head = nullptr;
    head = new List;
    head->m_key = 0;
    head->next = nullptr;

    *head = createList(head);

    for(int i = 0; i < 5; i++)
    {
        if(head != nullptr)
        {
            cout << head->m_key << endl;
            List * tp = head->next;
            head = tp;
        }
    }
}
