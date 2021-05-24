#include <iostream>
#include <vector>

void bubble1(std::vector<int> a, int a_size)
{
    for (int i = 0; i < a_size - 1; i++) {
        for (int j = 1; j < a_size - i; j++) {
            if (a[j - 1] > a[j]) {
                std::swap(a[j - 1], a[j]);
            }
        }
    }

}

void bubble2(std::vector<int> &a, int a_size)
{
    int j, k;
    int index;
    index = a_size;
    while (index > 0)
    {
        k = index;
        index = 0;
        for (j = 1; j < k; j++)
            if (a[j - 1] > a[j])
            {
                std::swap(a[j - 1], a[j]);
                index = j;
            }
    }
}

int main(int argc, char** argv)
{
    std::vector<int> a = {1, 4, 6, 66, 22, 33, 9, 20};
    int a_size = a.size();
    bubble2(a, a_size);
    for(auto &s : a)
    {
        std::cout << s << std::endl;
    }

    return 0;
}
