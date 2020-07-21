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

int main(int argc, char **argv)
{
    SqSrack s;

    int size, increment, i;

    size = max_size;
    increment = max_size;
    int e, eArr[5] = {1, 2, 3, 4, 5};
    
    if(!initStack(s, size, increment))
    {
        cout << "Eroor = initStack" << endl;
        exit(0);
    }

    //push
    for(int i = 0; i < max_size; ++i)
    {
        if(!Push_sq(s, eArr[i]))
        {
            cout << "Error = push_q" << endl;
            exit(0);
/bin/bash: k：未找到命令
    }
}
