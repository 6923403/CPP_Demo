#include <iostream>
#include <vector>
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

std::vector<int> sort(std::vector<int> a)
{
    int max_index = f_max(a);
    std::vector<int> re(v_size, 0);

    int j, k;
    int base = 10;
    while(max_index--)
    {
        std::vector<int> count(v_size, 0);
        for(int i = 1; i < v_size; i++)
        {
            int index = a[i] / base % 10;
            count[index]++;
        }

        std::vector<int> start(v_size, 0);
        for(int i = 1; i < v_size; i++)
        {
            start[i] = count[i - 1] + start[i - 1];
        }

        for(int j = 0; j < v_size; j++)
        {
            int index = a[j] / base % 10;
            re[start[index]++] = a[j];
        }

        base *= 10;
        show(re);
    }

    return re;
}

int main(int argc, char** argv)
{
    std::vector<int> a = {2, 12, 30, 9, 50, 82, 28, 77, 12};
    std::vector<int > re = {};
    v_size = a.size();
    re = sort(a);
    show(re);
    return 0;
}
