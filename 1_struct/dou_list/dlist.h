#ifndef CPP_DEMO_DLIST_H
#define CPP_DEMO_DLIST_H

#include <iostream>

struct DNode
{
    DNode* prev;
    DNode* next;
    int data;
};

class Dlist {
public:
    Dlist();
    ~Dlist();

    void init();
    void insert(int num);
    void insert(int num, int index);
    void del_list(int index);

    void show();

private:
    DNode* list;
    DNode* end;
};


#endif //CPP_DEMO_DLIST_H
