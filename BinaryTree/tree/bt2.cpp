#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct BTNode
{
    int data;
    struct BTNode *left;
    struct BTNode *right;
} BTNode, *BTree;

void initBTree(BTree &T)
{
    T = NULL;
}

bool BTreeEmpty(BTree &T)
{
    if(NULL == T)
        return false;

    return true;
}

char data[5] = {'A', 'B', 'C', 'D', 'E'};
void MakeBTree(BTree &T)
{
    T = new BTNode();
    if(T == NULL)
        exit(0);

    T->data = data[0];
    T->left = NULL;
    T->right = NULL;
}

int main(int argc, char **argv)
{
    BTree Tree = NULL;
    BTree Temp = NULL;

    initBTree(Tree);

    if(BTreeEmpty(Tree))
        cout << "Tree is NULL" << endl;
    else
        exit(0);

    MakeBTree(Tree);

    return 0;
}
