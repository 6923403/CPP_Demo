#include <iostream>
#include <stdlib.h>
using namespace std;

const int max_size = 5;

typedef struct
{
    int *elem;
    int top;
    int size;
    int increment;
} SqSrack;

int initStack(SqSrack &s, int size, int inc);
int Push_sq(SqSrack &s, int e);
void showSq(SqSrack s);
int Stack_empty(SqSrack s);
int Pop_Sq(SqSrack s);
void ClearStack(SqSrack &s);


int Push_sq(SqSrack &s, int e)
{
    int * newBase;
    if(s.top >= s.size)
    {
        newBase = new int;
        if(newBase == NULL)
            return 0;
        s.elem = newBase;
        s.size += s.increment;
    }
    s.elem[s.top++] = e;
    return 1;
}

int initStack(SqSrack &s, int size, int inc)
{
    s.elem = new int;
    if(s.elem == NULL)
        return 0;
    s.top = 0;
    s.size = max_size;
    s.increment = inc;
    return 1;
}

int Stack_empty(SqSrack s)
{
    if(s.top == 0)
        return 1;

    return 0;
}

int Pop_Sq(SqSrack s)
{   
    return s.elem[s.top - 1];
}

void ClearStack(SqSrack &s)
{
    if (s.top == 0)
        return;
    s.size = 0;
    s.top = 0;

    cout << "Clear_Stack ." << endl;
}

void showSq(SqSrack s)
{
    while(s.top-- != -1)
    {
        cout << s.elem[s.top];
    }
}

int main(int argc, char **argv)
{
    SqSrack s;

    int size, increment;

    size = max_size;
    increment = max_size;
    int eArr[5] = {1, 2, 3, 4, 5};
    
    if(!initStack(s, size, increment))
    {
        cout << "Eroor = initStack" << endl;
        exit(0);
    }

    /*
     * push stack
     */
    for(int i = 0; i < max_size; ++i)
    {
        if(!Push_sq(s, eArr[i]))
        {
            cout << "Error = push_sq" << endl;
            exit(0);
        }
    }

    /*
     * Stack Full
     */
    if(Stack_empty(s))
        cout << "Stak is full ." << endl;
    else
        cout << "Stack is NULL ." << endl;

    /*
     * Pop stack
     */
    cout << "Pop_Sq = " << Pop_Sq(s) << endl;

    /*
     * show stack
     */
    showSq(s);

    /*
     * Clear Stack
     */
    cout << endl;
    ClearStack(s);

    return 0;
}
