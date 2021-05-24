#include "bt.h"

//https://blog.csdn.net/alzzw/article/details/97633941
//https://blog.csdn.net/alzzw/article/details/97663352

int main(int argc, char** argv)
{
    BTree bt;
    std::vector<int > a = {3, 5, 7, 9, 11, 44, 55, 22, 25};
    int asize = a.size();
    for(int i = 0; i < asize; i++) {
        bt.insert_tree(a[i]);
    }

    return 0;
}
