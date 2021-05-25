#include <iostream>
#include <vector>

int a_size = 0;
void show(std::vector<int> a);

void max_heap(std::vector<int> &a, int i, int len)
{
    int index = i;
    int m = i * 2 + 1;
    while(m <= len)
    {

        show(a);
        if(m + 1 <= len && a[m] < a[m + 1])
        {
            m++;
        }
        if(a[index] > a[m])
        {
            return;
        }
        else
        {
            std::swap(a[index], a[m]);
            index = m;
            m = index * 2 + 1;
        }
    }
}

void h_sort(std::vector<int> &a)
{
    int i;
    for(i = a_size / 2; i >= 0; i--)
    {
        max_heap(a, i, a_size - 1);
    }
    std::cout << "a_size - 1" << std::endl;
    for(i = a_size - 1; i > 0; i--) {
        std::swap(a[0], a[i]);
        max_heap(a, 0, i - 1);
    }
}

void show(std::vector<int> a)
{
    for(auto &s : a)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::vector<int> a = {20, 30, 40, 50, 10, 19, 29};
    a_size = a.size();

    h_sort(a);
    return 0;
}