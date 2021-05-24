#include "bt.h"

BTree::BTree() : tree(nullptr), parent(nullptr)
{

}

BTree::~BTree()
{

}

void BTree::insert_tree(int key)
{
    if(tree == nullptr)
    {
        tree = new BTree;
        int data_s = data.size();
        if(data_s < m_max)
        {
            tree->data.push_back(key);
        }
    }

}

