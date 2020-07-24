#include <iostream>
using namespace std;
#define MAX_SIZE 20

typedef struct
{
    int data[MAX_SIZE];
    int top;
}Sqtack;

Sqtack * Push(Sqtack *ac)
{
    for(int i = 0; i < 5; i++) {
        ac->data[ac->top] = i;
        ac->top++;
    }
    return ac;
}

Sqtack * Pop(Sqtack *ac)
{
    while(ac->top != -1)
    {
        cout << ac->data[ac->top] << endl;
        ac->top--;
    }

    return ac;
}

void test1()
{
    Sqtack * ac = new Sqtack;
    ac = Push(ac);
    for(int k = 0; k < 5; k++)
    {
        cout << ac->data[k] << endl;
    }
    
    ac = Pop(ac);
    cout << ac->data[3] << endl;
}

int main(int argc, char **argv)
{
    test1();
    
    return 0;
}
