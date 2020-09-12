#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode * createlist()
{
    ListNode * l = new ListNode(0);
    ListNode * p = l;

    int t = 0;
    for(int i = 0; i < 4; i++)
    {
        ListNode * newNode = new ListNode(0);
        cin >> t;
        newNode->val = t;
        newNode->next = NULL;

        p->next = newNode;
        p = newNode;
    }

    p->next = NULL;
    return l->next;
}

ListNode * twosum(ListNode * l1, ListNode * l2)
{
    int ten = 0;
    int sum = 0;

    ListNode *res = new ListNode(0);
    ListNode *p = res;

    while(l1 || l2 || ten != 0)
    {
        sum = 0;
        sum += ten;
        ten = 0;

        if(l1)
        {
            sum += l1->val;
            l1 = l1->next;
        }

        if(l2)
        {
            sum += l2->val;
            l2 = l2->next;
        }

        p->val = sum % 10;
        ten = sum / 10;

        if(l1 || l2 || ten != 0)
        {
            ListNode * newnode = new ListNode(0);
            newnode->next = NULL;
            p->next = newnode;
            p = newnode;
        }
    }
    p->next = NULL;
    return res;
}

void showlist(ListNode *l1)
{
    for(int i = 0; i < 4; i++)
    {
        cout << l1->val << endl;
        l1 = l1->next;
    }
}

int main()
{
    ListNode *rec = new ListNode(0);

    cout << "create list1" << endl;
    ListNode *l1 = createlist();

    cout << "create list2" << endl;
    ListNode *l2 = createlist();

    rec = twosum(l1, l2);

    cout << "show rec" << endl;
    showlist(rec);
}
