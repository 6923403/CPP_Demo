#include <iostream>
#include <limits>
#include <vector>
int v_size = 0;

void show(std::vector<int> re)
{
    for(auto &s : re)
    {
        std::cout << s << " ";
    }

    std::cout << std::endl;
}

void Merge(std::vector<int> &a, int front, int mid, int end)
{
    std::vector<int> temp(end, 0);
    int i = front;
    int j = mid + 1;
    int k = 0;

    while(i <= mid && j <= end)
    {
        if(a[i] < a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = a[i++];
    }

    while (j <= end)
    {
        temp[k++] = a[j++];
    }

    //将临时区域中排序后的元素，整合到原数组中
    for (i = 0; i < k; i++)
    {
        a[front + i] = temp[i];
    }
}

void sort(std::vector<int> &a, int front, int end)
{
    if(front >= end)
        return;
    int mid = (front + end) / 2;
    sort(a, front, mid);
    sort(a, mid + 1, end);
    Merge(a, front, mid, end);
}

int main(int argc, char** argv)
{
    std::vector<int> a = {8, 4, 5, 7, 1, 3, 6, 2};
    v_size = a.size();
    int front = 0;
    int end = a.size();

    sort(a, front, end - 1);

    show(a);
    return 0;
}