#include <iostream>
using namespace std;

typedef struct StackNode
{
    int data;
    StackNode * next;
};

typedef struct LinkStack
{
    StackNode * top;
    int count;
};

int initLinkStack(LinkStack * stack)
{
    if(!stack)
    {
        return 0;
    }

    stack->top = nullptr;
    stack->count = 0;
    return 1;

}

int push_stack(LinkStack *stack, int e)
{
    if(!stack)
    {
        return 0;
    }

    StackNode * node = new StackNode;
    node->data = e;
    node->next = stack->top;
    stack->top = node;
    stack->count++;

    return 1;
}

void show_Stack(LinkStack * stack)
{
    if(!stack && stack->count)
    {
        cout << "NUll" << endl;
        return; 
    }

    StackNode * node = stack->top;
    while(node)
    {
        cout << "Data = " << node->data << endl;
        node = node->next;
    }

}

void pop_stack(LinkStack * stack)
{
    if(!stack && stack->count)
    {
        cout << "Null "<< endl;
    }
    StackNode * node = stack->top;
    stack->top = node->next;
    free(node);
    stack->count--;
}

int main(int argc, char **argv)
{
    LinkStack stack;
    initLinkStack(&stack);
    push_stack(&stack, 5);
    push_stack(&stack, 9);
    push_stack(&stack, 12);

    show_Stack(&stack);

    pop_stack(&stack);
    cout << endl;
    show_Stack(&stack);

    return 0;
}
