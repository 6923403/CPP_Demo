#include <iostream>

typedef struct CSNode
{
    TElemType data;
    struct CSNode * firstchild, * rightsib;
} CSNode, *CSTree;

