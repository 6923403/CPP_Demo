#include <iostream>
#include <exception>
using namespace std;

class MyLinkedList {
public:
    struct List
    {
        int val;
        List *next;
        List() : val(0), next(nullptr)
        {}
        List(int x) : val(x), next(nullptr)
        {}
    };
    /** Initialize your data structure here. */
    MyLinkedList() {
        head = new List;
        list_len = 0;
    }

    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
        if(index > list_len -1)
        {
            return -1;
        }
        else if(index == 0)
        {
            return head->next->val;
        }

        List *p = head;
        while(index--)
        {
            p = p->next;
        }

        return p->next->val;
    }

    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        List *add = new List(val);
        add->next = head->next;
        head->next = add;
        list_len++;
    }

    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        List *add = new List(val);
        List *p = head;
        while(p->next)
        {
            p = p->next;
        }

        p->next = add;
        add->next = nullptr;
        list_len++;
    }

    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if(index > list_len)
        {
            return;
        }
        else if(index == 0)
        {
            List *p = head;
            List *add = new List(val);
            add->next = p->next;
            p->next = add;
            list_len++;
        }
        else
        {
            List *p = head;
            while(index--)
            {
                p = p->next;
            }
            List *add = new List(val);
            add->next = p->next;
            p->next = add;
            list_len++;
        }

    }

    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        if(index >= list_len || index < 0)
        {
            return;
        }
        else
        {
            List *p = head;
            while(index--)
            {
                p = p->next;
            }
            List *tmp = p->next;
            p->next = p->next->next;
            delete tmp;
            list_len--;
        }

    }
private:
    List *head;
    int list_len;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */

int main()
{
    MyLinkedList *linkedList = new MyLinkedList();
    linkedList->addAtHead(2);
    linkedList->deleteAtIndex(1);
    //linkedList->addAtHead(2);
    //linkedList->addAtHead(7);
    //linkedList->addAtHead(3);
    linkedList->addAtHead(2);
    linkedList->addAtHead(5);

    cout << "细节太多" << endl;
    //["MyLinkedList","addAtHead","deleteAtIndex","addAtHead","addAtHead","addAtHead","addAtHead","addAtHead","addAtTail","get","deleteAtIndex","deleteAtIndex"]
    //[[],[2],[1],[2],[7],[3],[2],[5],[5],[5],[6],[4]]
    return 0;
}