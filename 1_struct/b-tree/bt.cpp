#include "bt.h"

BTree::BTree() : tree(nullptr), parent(nullptr)
{

}

BTree::~BTree()
{

}

void BTree::create_tree(int key2)
{
    BTree* node = nullptr;
    if(tree == nullptr)
    {
        int t_size = key.size();
        if(t_size < m_max)
        {
            key.push_back(key2);
        }
    }
}

