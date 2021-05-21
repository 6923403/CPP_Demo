#ifndef BT_H
#define BT_H

#include <iostream>
#include <cstdlib>
#include <vector>
/*
 * 每个节点最多有m-1个关键字（可以存有的键值对）。
 * 根节点最少可以只有1个关键字。
 * 非根节点至少有m/2个关键字。
 * 每个节点中的关键字都按照从小到大的顺序排列，每个关键字的左子树中的所有关键字都小于它，而右子树中的所有关键字都大于它。
 * 所有叶子节点都位于同一层，或者说根节点到每个叶子节点的长度都相同。
 * 每个节点都存有索引和数据，也就是对应的key和value。
 */

//https://www.yiibai.com/data_structure/b-tree.html
//https://www.cs.usfca.edu/~galles/visualization/BTree.html
//https://blog.csdn.net/geek_jerome/article/details/78895289

const int m = 4; //4阶
const int m_max = m - 1; //key 最大
const int m_min = (m - 1) / 2; //key 最小

class BTree
{
public:
    BTree();
    ~BTree();

    void create_tree(int key);

private:
    BTree* tree;
    BTree* parent;

    int key2[m_max];
    std::vector<int> key;
    std::vector<BTree>* ptr;
};

#endif //BT_H