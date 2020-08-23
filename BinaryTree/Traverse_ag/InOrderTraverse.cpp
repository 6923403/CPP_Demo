#include <iostream>
using namespace std;

void InOrderTraverse(BiTree T)
{
    if(T == NULL)
        return;

    InOrderTraverse(T->lchild);
    cout << "T->data = " << T->data << endl;
    InOrderTraverse(T->rchild);
}

int main()
{

}
