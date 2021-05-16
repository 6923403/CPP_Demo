#include <iostream>
#include <algorithm>
#include <vector>
//https://blog.csdn.net/isunbin/article/details/81707606
//https://www.jianshu.com/p/fdb3c8c331f1

struct BNode
{
    int data;
    BNode* lchild, *rchild;
    int height;
};

int get_height(BNode *tree)
{
    if (tree == nullptr)
        return 0;
    return tree->height;
}

int getBalance(BNode* tree)
{
    if(tree == nullptr)
    {
        return 0;
    }
    else
    {
        return get_height(tree->lchild) - get_height(tree->rchild);
    }
}

void ll_rotate(BNode** tree)
{
    BNode *x = (*tree)->lchild;
    (*tree)->lchild = x->rchild;
    x->rchild = (*tree);

    (*tree)->height = std::max(get_height((*tree)->lchild), get_height((*tree)->rchild)) + 1;
    x->height = std::max(get_height(x->lchild), get_height(x->rchild)) + 1;
}

void rr_rotate(BNode** tree)
{
    BNode *x = (*tree)->rchild;
    (*tree)->rchild = x->lchild;
    x->lchild = *tree;

    (*tree)->height = std::max(get_height((*tree)->lchild), get_height((*tree)->rchild)) + 1;
    x->height = std::max(get_height(x->lchild), get_height(x->rchild)) + 1;
}

void insert(BNode **tree, int key)
{
    //默认不存在相等数据
    if(*tree == nullptr)
    {
        BNode* node = new BNode;
        node->data = key;
        node->lchild = nullptr;
        node->rchild = nullptr;
        node->height = 1;
        *tree = node;
    }
    else if((*tree)->data > key)
    {
        insert(&(*tree)->lchild, key);
    }
    else
    {
        insert(&(*tree)->rchild, key);
    }

    (*tree)->height = 1 + std::max(get_height((*tree)->lchild), get_height((*tree)->rchild));
    int balance = getBalance(*tree);
    if (balance > 1 && key < (*tree)->lchild->data) //LL型
    {
        ll_rotate(&(*tree));
    }
    else if (balance < -1 && key > (*tree)->rchild->data)     //RR型
    {
        rr_rotate(&(*tree));
    }
    else if (balance > 1 && key > (*tree)->lchild->data)     //LR型
    {
        rr_rotate(&(*tree)->lchild);
        ll_rotate(&(*tree));
    }
    else if (balance < -1 && key < (*tree)->rchild->data)     //RL型
    {
        ll_rotate(&(*tree)->rchild);
        rr_rotate(&(*tree));
    }
}

void show(BNode* tree)
{
    if(tree == nullptr) {
        return;
    }

    std::cout << tree->data << std::endl;
    show(tree->lchild);
    show(tree->rchild);
}

int main(int argc, char** argv)
{
    BNode* tree = nullptr;
    std::vector<int > a = {3,2,1,4,5,6,7,10,9,8};
    int sizea = a.size();
    for(int i = 0; i < sizea; i++)
    {
        insert(&tree, a[i]);
    }

    show(tree);

    return 0;
}