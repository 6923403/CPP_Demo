#include <iostream>
#include <vector>

const int Max_size = 100;

struct List
{
    int data[Max_size];
    int len;
};
void Init(List& list)
{
    memset(list.data, '\0', Max_size);
    list.len = 0;
}

void Create_list(List& list, int key)
{
    list.data[list.len] = key;
    list.len++;
}

void SelectSort(List& list)
{
    int temp = 0, min = 0;
    for(int i = 0; i < list.len; i++)
    {
        min = i;
        for(int j = i + 1; j < list.len; j++)
        {
            if(list.data[j] < list.data[min])
            {
                min = j;
            }
        }
        if(min != i)
        {
            temp = list.data[min];
            list.data[min] = list.data[i];
            list.data[i] = temp;
        }
    }
}

void show(List list)
{
    for(int i = 0; i < list.len; i++)
    {
        std::cout << list.data[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    List list;
    std::vector<int> a = {1, 5, 3, 4, 6, 7, 99};
    int a_size = a.size();
    Init(list);
    //在待排序数组中选出最小的(或最大)的与第一个位置的数据交换 然后在剩下的待排序数组中找出最小(或最大)的与第二个位置的数据交换，以此类推，直到第n-1个元素。
    for(int i = 0; i < a_size; i++)
    {
        Create_list(list, a[i]);
    }

    SelectSort(list);

    show(list);
    return 0;
}