#include <iostream>
//https://www.jianshu.com/p/c6cb2c1460d0
//https://blog.csdn.net/isunbin/article/details/81703762

typedef struct BiTNode {
    /* 结点数据 */
    int data;
    /* 左右孩子指针 */
    struct BiTNode *lchild, *rchild;
} BiTNode;

void insert(BiTNode **tree, int key)
{
    if(*tree == nullptr)
    {
        BiTNode* node = new BiTNode;
        node->data = key;
        node->lchild = nullptr;
        node->rchild = nullptr;
        *tree = node;
    }
    else if((*tree)->data > key)
    {
        insert(&(*tree)->lchild, key);
    }
    else if((*tree)->data < key)
    {
        insert(&(*tree)->rchild, key);
    }
    else
    {
        std::cout << "值相等 跳过" << std::endl;
    }
}

void show(BiTNode *tree)
{
    if(tree != nullptr) {
        std::cout << tree->data << std::endl;
        show(tree->lchild);
        show(tree->rchild);
    }
}

void delete_tree(BiTNode **tree)
{
    BiTNode *temp = nullptr;
    if((*tree)->lchild == nullptr)
    {
        temp = *tree;
        *tree = (*tree)->rchild;
    }
    else if((*tree)->rchild == nullptr)
    {
        temp = *tree;
        *tree = (*tree)->lchild;
    }
    else
    {
        BiTNode *s = nullptr;
        temp = *tree;
        temp = (*tree)->lchild;

        while(temp->rchild)
        {
            s = temp;
            temp = temp->rchild;
        }

        (*tree)->data = temp->data;

        if(s != *tree)
        {
            s->rchild = temp->lchild;
        }
        else
        {
            s->rchild = temp->rchild;
        }
    }

    delete temp;
}

void deleteleaf(BiTNode **tree)
{
    BiTNode *temp = *tree;
    *tree = nullptr;
    delete temp;
}

void tree_delete(BiTNode **tree, int key) //只有叶子
{
    if(*tree == nullptr)
    {
        return;
    }

    if((*tree)->data == key)
    {
        if((*tree)->lchild != nullptr || (*tree)->rchild != nullptr)
        {
            delete_tree(&(*tree));
        }
        else
        {
            deleteleaf(&(*tree));
        }
    }
    else if((*tree)->data > key)
    {
        tree_delete(&(*tree)->lchild, key);
    }
    else
        tree_delete(&(*tree)->rchild, key);
}

int main(int argc, char** argv)
{
    BiTNode* tree = nullptr;
    int a[] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 36, 29, 93};
    int asize = sizeof(a) / sizeof(a[0]);
    for(int i = 0; i < asize; i++)
    {
        insert(&tree, a[i]);
    }


    tree_delete(&tree, 47);
    show(tree);
    return 0;
}

