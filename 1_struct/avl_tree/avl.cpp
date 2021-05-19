#include <iostream>
#include <algorithm>
//https://blog.csdn.net/isunbin/article/details/81707606
//https://www.jianshu.com/p/fdb3c8c331f1
//https://www.jianshu.com/p/655d83f9ba7b

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
        return get_height(tree->lchild) - get_height(tree->rchild); //左树减右树
    }
}

void ll_rotate(BNode** tree)
{
    BNode *p = *tree;
    BNode *x = new BNode;
    x = p->lchild;
    p->lchild = x->rchild;
    x->rchild = p;

    (*tree)->height = std::max(get_height(p->lchild), get_height(p->rchild)) + 1;
    x->height = std::max(get_height(x->lchild), get_height(x->rchild)) + 1;

    *tree = x;
}

void rr_rotate(BNode** tree)
{
    BNode *p = *tree;
    BNode *x = new BNode;
    x = p->rchild;
    p->rchild = x->lchild;
    x->lchild = p;

    (*tree)->height = std::max(get_height(p->lchild), get_height(p->rchild)) + 1;
    x->height = std::max(get_height(x->lchild), get_height(x->rchild)) + 1;
    *tree = x;
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

    (*tree)->height = 1 + std::max(get_height((*tree)->lchild), get_height((*tree)->rchild)); //计算height
    int balance = getBalance(*tree); //计算平衡因子
    /*
     * balance大于1 是L  key小于左LL key大于左LR
     */
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

BNode* minValue(BNode* tree)
{
    BNode* temp = tree;
    while(temp->lchild != nullptr)
    {
        temp = temp->lchild;
    }

    return temp;
}

void delete_node(BNode** tree, int key)
{
    if(*tree == nullptr)
    {
        return;
    }
    if((*tree)->data < key)
    {
        delete_node(&(*tree)->rchild, key);
    }
    else if((*tree)->data > key)
    {
        delete_node(&(*tree)->lchild, key);
    }
    else
    {
        if(((*tree)->lchild == nullptr) || ((*tree)->rchild == nullptr))
        {
            BNode* temp = nullptr;
            if((*tree)->lchild == nullptr && (*tree)->rchild == nullptr)
            {
                temp = *tree;
                *tree = nullptr;
            }
            else {
                temp = (*tree)->lchild ? (*tree)->lchild : (*tree)->rchild;
                *tree = temp;
            }
            delete temp;
        }
        else
        {
            BNode* temp = minValue(*tree);
            (*tree)->data = temp->data;
            delete_node(&(*tree)->rchild, temp->data);
        }
    }

    if(*tree == nullptr)
    {
        return;
    }

    (*tree)->height = 1 + std::max(get_height((*tree)->lchild), get_height((*tree)->rchild));
    int balance = getBalance(*tree);

    if (balance > 1 && (*tree)->lchild->data >= 0) //LL型
    {
        ll_rotate(&(*tree));
    }
    else if (balance < -1 && (*tree)->rchild->data <= 0) //RR型
    {
        rr_rotate(&(*tree));
    }
    else if (balance > 1 && (*tree)->lchild->data < 0) //LR型
    {
        rr_rotate(&(*tree)->lchild);
        ll_rotate(&(*tree));
    }
    else if (balance < -1 && (*tree)->rchild->data > 0) //RL型
    {
        ll_rotate(&(*tree)->rchild);
        rr_rotate(&(*tree));
    }
}

int main(int argc, char** argv)
{
    BNode* tree = nullptr;
    int a[] = {3,2,1,4,5,6,7,10,9,8};
    int sizea = sizeof(a) / sizeof(a[0]);
    for(int i = 0; i < sizea; i++)
    {
        insert(&tree, a[i]);
    }
    std::cout << "show " << std::endl;

    //show(tree); //4 2 1 3 7 6 5 9 8 10
    int key = 5;
    delete_node(&tree, key);
    show(tree); //4 2 1 3 7 6 9 8 10

    return 0;
}