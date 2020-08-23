#include <iostream>
using namespace std;

void PostOrderTraverse(BiTree T)
{
    if(T == NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    cout << "T->data = " << T->data << endl;
}

int main()
{

}
ABCDEF
CB A EDF
CBEFDA
