#ifndef CPP_DEMO_LIST_H
#define CPP_DEMO_LIST_H

#include <iostream>

struct LNode
{
    int data;
    LNode* next;
};

class List
{
public:
    List();
    ~List();

    void init();
    void show();
    void Insert();
    void head_Insert();
    void Delete();

private:
    LNode* head;
    LNode* end;
    int len;

};

#endif //CPP_DEMO_LIST_H
