#include <iostream>

typedef struct BiTNode {
    /* 结点数据 */
    int data;
    /* 左右孩子指针 */
    struct BiTNode *lchild, *rchild;
} BiTNode;

void insert(BiTNode **tree, int key)
{
    BiTNode* node = new BiTNode;
    node->data = key;
    node->lchild = nullptr;
    node->rchild = nullptr;
    if(*tree == nullptr)
    {
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

void tree_delete(BiTNode **tree, int key) //只有叶子
{
    if((*tree)->data == key)
    {
        if((*tree)->lchild != nullptr || (*tree)->rchild != nullptr)
        {
            if((*tree)->lchild == nullptr)
            {
                deleer(&(*tree));
            }
            else if((*tree)->rchild == nullptr)
            {
                deletel(&(*tree));
            }
            else
            {
                deletep(&(*tree));
            }
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
    int a[] = { 62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
    int asize = sizeof(a) / sizeof(a[0]);
    for(int i = 0; i < asize; i++)
    {
        insert(&tree, a[i]);
    }

    show(tree);

    tree_delete(&tree, 47);
    return 0;
}

