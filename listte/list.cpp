#include <iostream>
using namespace std;

class List
{
    public:
        int data;
        List * link;
        List * next;
};

int create(List &L, int *data, int n)
{
    List *q, *p;
    int i;
    if(n < 10)
        return 0;

    L = nullptr;
    p = L;
    for(i = 0; i < n; i++)
    {

    }
}


int main(int argc, char **argv)
{
    const a_size = 10;
    int a[a_size], tmp;
    cout << "insert a[]" << endl;
    for(int i = 0; i < a_size; i++)
    {
        cout << "number: ";
        cin >> tmp;
        a[i] = tmp;
        cout << endl;
    }

    List *L, *head;
    cout << "创建链表L " << endl;
    if(create(L, a, a_size))
    {
        cout << "Error " << endl;
        return -1;
    }

}
