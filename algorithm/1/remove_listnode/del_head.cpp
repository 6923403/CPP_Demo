#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


ListNode * removeElements(ListNode* head, int val) {

    while (head != NULL && head->val == val) { // 注意这里不是if
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }

    // 删除非头结点
    ListNode* cur = head;
    while (cur != NULL && cur->next!= NULL) {
        if (cur->next->val == val) {
            ListNode* tmp = cur->next;
            cur->next = cur->next->next;
            delete tmp;
        } else {
            cur = cur->next;
        }
    }
    return head;

}

void createlist(ListNode * node, char s[7])
{
    ListNode *p = node;
    for(int i = 0; i < 7; i++)
    {
        ListNode *q = new ListNode(0);
        q->val = s[i];
        q->next = NULL;
        p->next = q;
        p = q;
    }
}

void shownode(ListNode * node)
{
    for (ListNode *p = node; NULL != p; p = p->next) {
        cout << p->val << endl;
    }
}

int main(int argc, char **argv)
{
    ListNode * node = new ListNode(0);
    node->next = NULL;
    char s[7] = {1,2,6,3,4,5,6};

    createlist(node, s);

    int val = 6;
    removeElements(node, val);

    shownode(node);
    return 0;
}
