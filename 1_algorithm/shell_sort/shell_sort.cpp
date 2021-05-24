#include <iostream>
#include <vector>

//https://www.jianshu.com/p/d730ae586cf3

void show(std::vector<int> a)
{
    for(auto &s : a)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
}

void sort(std::vector<int > &a)
{
    int a_size = a.size();
    int increment = a_size / 2;
    while(increment >= 1)
    {
        for(int i = increment; i < a_size; i++)
        {
            for(int j = i - increment; j >= 0; j -= increment)
            {
                if(a[j] > a[j + increment])
                {
                    std::swap(a[j], a[j + increment]);
                }
            }
        }

        std::cout << "increment = " << increment << std::endl;
        show(a);
        increment = increment / 2;
    }
}

int main(int argc, char** argv)
{
    std::vector<int> a = {9, 500, 22, 20, 82, 99, 101, 200};
    show(a);

    sort(a);

    return 0;
}
