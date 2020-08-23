#include "BT.h"

using namespace std;

int main()
{
    char data[23] = {'-', '+', 'a', '#', '#', '*', 'b', '#', '#', '-', 'c', '#', '#', 'd', '#', '#', '/', 'e', '#', '#', 'f', '#', '#'};

    Tree tree;

    treeCreate(tree, data);

    printf("\n\n先序遍历二叉树结果: ");
    preorderTraversal(tree);
    printf("\n\n中序遍历二叉树结果: ");
    inorderTraversal(tree);
    printf("\n\n后序遍历二叉树结果: ");
    postorderTraversal(tree);
}
