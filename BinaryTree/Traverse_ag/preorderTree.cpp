#include <iostream>
using namespace std;

void PreOrderTraverse(BiTree T)
{
    if(T == NULL)
        return;

    std::cout << "T_data = " < T->data << std::endl;

    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

int mian()
{

}
