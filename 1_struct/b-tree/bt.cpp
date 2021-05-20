#include <iostream>
/*
 * 如果根结点不是叶结点，则其至少有两棵子树。
 * 每一个非根的分支结点都有k-1个元素和k个孩子，其中。每一个叶子结点n都有k-1个元素。
 * 所有叶子结点都位于同一层次。 所有分支结点包含下列信息数据
 */
//https://www.yiibai.com/data_structure/b-tree.html
//https://blog.csdn.net/yantingtao_sunny/article/details/51231934
//https://www.cs.usfca.edu/~galles/visualization/BTree.html
const int M = 3;
const int M_min = M / 2;