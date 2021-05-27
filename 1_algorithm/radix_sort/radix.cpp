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

int f_max(std::vector<int> a)
{
    int index = 0;
    int base = 10;
    for(int i = 0; i < v_size; i++)
    {
        while(a[i] > base)
        {
            index++;
            base *= 10;
        }
    }

    return index;
}

void sort(std::vector<int> a, std::vector<int> &re)
{
    int max_index = f_max(a);

    int j, k;
    int base = 1;
    std::vector<int> count(10, 0);
    while(max_index--)
    {
        for(int i = 0; i < v_size; i++)
        {
            int index = a[i] / base % 10;
            count[index]++;
        }

        std::vector<int> start(v_size, 0);
        for(j = 1; j < 10; j++)
        {
            count[j] = count[j - 1] + count[j];
        }

        for(k = 0; k < v_size; k++)
        {
            int index = a[k] / base % 10;
            re[start[index]++] = a[k];
        }

        base *= 10;
    }

}

int main(int argc, char** argv)
{
    std::vector<int> a = {2, 12, 30, 9, 50, 82, 28, 77, 120};
    std::vector<int > re(10, 0);
    v_size = a.size();
    sort(a, re);
    show(re);
    return 0;
}
