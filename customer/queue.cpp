#include "queue.h"
#include <cstdlib.h>

Queue::Queue(int qs) : qsize(qs)
{
    front = read = NULL;
    items = 0;
}

Queue::~Queue()
{
    Node * temp;
    while(front != NULL)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}

bool Queue::isempty() const
{
    return items == 0;
}

bool Queue::isfull() const
{
    return items == qsize;
}

int Queue::queuecount() const
{
    return items;
}

bool Queue::enqueue(const Item & item)
{
    if(isfull())
        return false;
    Node * add = new Node;
    /*
     * on failure, new throws  std::bad_alloc exception
     */
    add->item = item;
    add->nest = nullptr;
    items++;
    if(front == NULL)
        front = add;
    else
        read->next = add;
    read = add;
    return true;
}

bool Queue::dequeue(Item & item)
{
    if(front == NULL)
        return false;
    item = front->item;
    items--;
    Node * temp = front;
    front = front->next;
    delete temp;
    if(items == 0)
        read = NULL;
    return true;
}

void Customer::set(long when)
{
    prcesstime = std::rand() % 3 + 1;
    arrive = when;
}
