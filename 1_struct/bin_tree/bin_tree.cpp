#include <iostream>
#include <cstdlib>
/*
 * https://developer.aliyun.com/article/48634
 * https://www.cnblogs.com/wuyudong/p/c-transfer-point.html
 * https://github.com/huihut/interview/blob/master/DataStructure/BinaryTree.cpp
 * https://blog.csdn.net/lady_killer9/article/details/86377635
 */

struct BTNode
{
    int data;
    BTNode* lchild, *rchild;
};

BTNode* init_tree()
{
    int a;
    BTNode* tree;
    std::cout << "输入a: ";
    std::cin >> a;
    if(-1 == a)
    {
        tree = nullptr;
    }
    else
    {
        tree = new BTNode;
        tree->data = a;
        tree->lchild = init_tree();
        tree->rchild = init_tree();
    }

    return tree;
}

//先序遍历
void Preorder(BTNode* tree)
{
    if(tree) {
        std::cout << "tree->data: " << tree->data << std::endl;
        Preorder(tree->lchild);
        Preorder(tree->rchild);
    }
}

void InOrder(BTNode* tree)
{
    if(tree)
    {
        InOrder(tree->lchild);//递归中序遍历左右子树
        std::cout << "tree->data: " << tree->data << std::endl;
        InOrder(tree->rchild);
    }
}

void PostOrder(BTNode* tree)
{
    if(tree)
    {
        PostOrder(tree->lchild);//递归中序遍历左右子树
        PostOrder(tree->rchild);
        std::cout << "tree->data: " << tree->data << std::endl;
    }
}

void test1()
{
    BTNode* tree;
    tree = init_tree();
    std::cout << "前序遍历" << std::endl;
    Preorder(tree);
    std::cout << "中序遍历" << std::endl;
    InOrder(tree);
    std::cout << "后序遍历" << std::endl;
    PostOrder(tree);
}

int main(int argc, char** argv)
{
    test1();

    return 0;
}