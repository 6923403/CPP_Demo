#ifndef _BT_H_
#define _BT_H_

#include <iostream>
#include <cstdlib>

typedef struct Node
{
    char data;
    Node * lchild;
    Node * rchild;
} *Tree;

static int index = 0;

void treeCreate(Tree &tree, char data[])
{
    char e = data[index++];
    if(e == '#')
    {
        tree = NULL;
    }
    else
    {
        tree = new Node;
        tree->data = e;
        treeCreate(tree->lchild, data);
        treeCreate(tree->rchild, data);
    }
}

void preorderTraversal(Tree tree)
{
    if(tree == NULL)
        return;

    printf("%c  ", tree->data);
    preorderTraversal(tree->lchild);
    preorderTraversal(tree->rchild);
}

void inorderTraversal(Tree tree)
{
    if(tree == NULL)
        return;

    inorderTraversal(tree->lchild);
    printf("%c  ", tree->data);
    inorderTraversal(tree->rchild);
}

void postorderTraversal(Tree tree)
{
    if(tree == NULL)
        return;
    postorderTraversal(tree->lchild);
    postorderTraversal(tree->rchild);
    printf("%c  ", tree->data);
}

#endif //_BT_H_
