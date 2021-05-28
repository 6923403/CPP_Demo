#include <iostream>
#include <vector>
//https://zhuanlan.zhihu.com/p/126116878
int v_size;

void show(std::vector<int> re)
{
    for(auto &s : re)
    {
        std::cout << s << " ";
    }

    std::cout << std::endl;
}

int maxbit(std::vector<int> a, int n) //辅助函数，求数据的最大位数
{
    int maxData = a[0];              ///< 最大数
    /// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
    for (int i = 1; i < n; ++i)
    {
        if (maxData < a[i])
            maxData = a[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p *= 10; // Maybe overflow
        maxData /= 10;
        ++d;
    }

    return d;
}
std::vector<int> sort(std::vector<int> a, int n) //基数排序
{
    int d = maxbit(a, n);

    std::vector<int> tmp(n, 0);

    int i, j, k;
    int radix = 1;

    for(i = 1; i <= d; i++) //进行d次排序
    {
        std::vector<int> count(10, 0);
        for(j = 0; j < n; j++)
        {
            k = (a[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
        {
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        }
        show(count);

        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (a[j] / radix) % 10;
            tmp[count[k] - 1] = a[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            a[j] = tmp[j];
        radix = radix * 10;
    }

    return a;
}

int main(int argc, char** argv)
{
    std::vector<int> a = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
    v_size = a.size();
    std::vector<int> re(v_size, 0);
    re = sort(a, v_size);
    show(re);
    return 0;
}