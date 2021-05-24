#include <iostream>
#include <vector>

void insert_sort(std::vector<int> &a)
{
    int a_size = a.size();
    int num = 0;
    for(int i = 1; i < a_size; i++)
    {
       //2, 44, 12, 33, 55, 99, 20
        num = a[i];
        std::cout << "a[i] = " << a[i];
        int j;
        for(int j = i - 1; j >= 0; j--)
        {
            if(a[j] > num)
            {
                std::cout << " a[j] = " << std::endl;
                a[j + 1] = a[j];
            }
            else
                break;
        }
        a[j + 1] = num;
    }
}

int main(int argc, char** argv)
{
    std::vector<int> a = {2, 44, 12, 33, 55, 99, 20};
    std::cout << "insert" << std::endl;
    insert_sort(a);
    for(auto &s : a)
    {
        std::cout << s << std::endl;
    }
}
