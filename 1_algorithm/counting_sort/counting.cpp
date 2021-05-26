#include <iostream>
#include <vector>

int v_size = 0;
void show(std::vector<int> re)
{
    for(int i = 0; i < v_size; i++)
        if(re[i] != 0)
        {
            for (int k = re[i]; k > 0; k--)
            {
                std::cout << i << " ";
            }
        }
    std::cout << std::endl;
}

std::vector<int> sort(std::vector<int> a)
{
    std::vector<int> count(v_size, 0);
    int i, j, k;
    for(i = 0; i < v_size; i++)
    {
        count[a[i]]++;
    }

    return count;
}

int main(int argc, char** argv)
{
    std::vector<int> a = {1, 2, 4, 2, 1, 2, 2, 2, 4, 5, 9, 9, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    v_size = a.size();

    std::vector<int> re;
    //选出最大 这里默认小于10
    //像哈希
t
    re = sort(a);
    show(re);

    return 0;
}
