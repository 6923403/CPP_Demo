#include <iostream>
using namespace std;


//5个常量定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

//类型定义
typedef int Status;
typedef int ElemType;

//链表的类型
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList; 

Status InitList_L(LinkList &L);
Status DestroyList_L(LinkList &L);
Status ClearList_L(LinkList &L);
Status ListEmpty_L(LinkList L);
int ListLength_L(LinkList L);
LNode* Search_L(LinkList L, ElemType e);
LNode* NextElem_L(LNode *p);
Status InsertAfter_L(LNode *p, LNode *q);
Status DeleteAfter_L(LNode *p, ElemType &e);
void ListTraverse_L(LinkList L, Status(*visit)(ElemType e));


//创建包含n个元素的链表L，元素值存储在data数组中
Status create(LinkList &L, ElemType *data, int n) {
    LNode *p, *q;
    int i;
    if (n < 0) return ERROR;
    L = NULL;
    p = L;
    for (i = 0; i < n; i++)
    {
        q = (LNode *)malloc(sizeof(LNode));
        if (NULL == q) return OVERFLOW;
        q->data = data[i];
        q->next = NULL;
        if (NULL == p) L = q;
        else p->next = q;
        p = q;
    }
    return OK;
}

//e从链表末尾入链表
Status EnQueue_LQ(LinkList &L, ElemType &e) {
    LinkList p, q;

    if (NULL == (q = (LNode *)malloc(sizeof(LNode)))) return OVERFLOW;
    q->data = e;
    q->next = NULL;
    if (NULL == L) L = q;
    else
    {
        p = L;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = q;
    }
    return OK;
}


//从链表头节点出链表到e
Status DeQueue_LQ(LinkList &L, ElemType &e) {
    if (NULL == L) return ERROR;
    LinkList p;
    p = L;
    e = p->data;
    L = L->next;
    free(p);
    return OK;
}

//遍历调用
Status visit(ElemType e) {
    printf("%d   ", e);
    return 1;
}

//遍历单链表
void ListTraverse_L(LinkList L, Status(*visit)(ElemType e))
{
    if (NULL == L) return;
    for (LinkList p = L; p != nullptr; p = p -> next) {
        visit(p -> data);
    }
}

int main(int argc, char **argv) {
    int i;
    const int a_size = 10;
    ElemType e, data[a_size] = { 1, 2, 3, 4, 5 };
    LinkList L;

    //显示测试值
    printf("---【单链表】---\n");
    printf("待测试元素为：\n");
    for (i = 0; i < a_size; i++) 
        cout << data[i] << endl;

    //创建链表L
    printf("创建链表L\n");
    if (ERROR == create(L, data, a_size))
    {
        printf("创建链表L失败\n");
        return -1;
    }
    cout << "list ok " << endl;

    //遍历单链表
    printf("此时链表中元素为：\n");
    ListTraverse_L(L, visit);
    cout << endl;

#if 0
    //从链表头节点出链表到e
    printf("\n出链表到e\n");
    DeQueue_LQ(L, e);
    printf("出链表的元素为：%d\n", e);
    printf("此时链表中元素为：\n");
    //遍历单链表
    ListTraverse_L(L, visit);

    //e从链表末尾入链表
    printf("\ne入链表\n");
    EnQueue_LQ(L, e);
    printf("入链表的元素为：%d\n", e);
    printf("此时链表中元素为：\n");
    //遍历单链表
    ListTraverse_L(L, visit);
    printf("\n");

#endif
    return 0;
}
