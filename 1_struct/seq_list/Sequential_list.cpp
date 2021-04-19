#include <iostream>
#include <cstdlib>

const int Max_size = 100;
const int N = 8;

typedef struct Sequential_list
{
    int* data;
    int len;
}Sqlist;

void show(Sqlist* list)
{
    for(int i = 0; i < list->len; i++)
    {
        std::cout << list->data[i] << " ";
    }

    std::cout << std::endl;
}

void init(Sqlist* list)
{
    list->data = new int[Max_size];
    if(!list->data)
    {
        std::cout << "init faild" << std::endl;
        delete list;
        exit(-1);
    }
    list->len = 0;
}

void create_list(Sqlist* list)
{
    for(int i = 0; i < 5; i++)
    {
        list->data[i] = i;
        list->len++;
    }

    show(list);
}

void insert(Sqlist* list, int num)
{
    int index = 2;
    if(index > list->len && list->len >= Max_size)
    {
        return;
    }

    for(int k = list->len; k >= index - 1; k--)
    {
        list->data[k + 1] = list->data[k];
    }
    list->data[index - 1] = num;
    list->len++;
    show(list);
}

void sort(Sqlist* list)
{
    int temp = 0;
    for(int i = 0; i < list->len - 1; i++)
    {
        if(list->data[i] > list->data[i + 1])
        {
            temp = list->data[i];
            list->data[i] = list->data[i + 1];
            list->data[i + 1] = temp;
        }
    }
    show(list);
}

void add(Sqlist* list, int num)
{
    if(list->len >= Max_size)
    {
        return;
    }

    list->data[list->len] = num;
    list->len++;
    show(list);
}

void delete_list(Sqlist* list, int index)
{
    if(index > list->len)
    {
        return;
    }

    for(int i = index; i < list->len; i++)
    {
        list->data[i - 1] = list->data[i];
    }
    list->len--;
    show(list);
}

void reverse(Sqlist* list)
{
    int temp = 0;
    std::cout << list->len << std::endl;
    for(int i = 0; i < list->len - i; i++)
    {
        temp = list->data[i];
        list->data[i] = list->data[list->len - 1 - i];
        list->data[list->len - 1 - i] = temp;
    }
    show(list);
}
void show2(Sqlist& list2)
{
    for(int k = 0; k < N; k++)
    {
        std::cout << list2.data[k] << " ";
    }
    std::cout << std::endl;
}

void CycleLeft(Sqlist& list2)
{
    //n(n>1)个整数放到一维数组R中，将R中保存的顺序序列循环左移p(0<p<n)个位置，
    //即R中数据由(X0,X1...Xn-1)变换为(Xp,Xp+1...Xn-1,X0,...Xp-1)
    const int p = 4;
    int t = 1;
    for(int i = 0; i < N; i++)
    {
        list2.data[i] = t;
        t++;
    }

    //12345678
    //56781234
    int temp = 0;
    for(int k = 0; k < p; k++)
    {
        temp = list2.data[k];
        list2.data[k] = list2.data[k + p];
        list2.data[k + p] = temp;
    }

    show2(list2);

}

void test()
{
    Sqlist* list = new Sqlist();
    init(list);
    create_list(list);
    insert(list, 5);
    sort(list);
    add(list, 6);
    delete_list(list, 5);
    reverse(list);

    delete list->data;
    delete list;
}

void test2() {
    Sqlist list2;
    list2.data = new int(N);
    CycleLeft(list2);

    delete list2.data;
}

int main()
{
    test2();

    return 0;
}