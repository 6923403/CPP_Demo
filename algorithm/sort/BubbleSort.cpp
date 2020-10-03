#include <iostream>
#include <vector>

using namespace std;

void bubble_sort1(vector<int> vec)
{
    int len = vec.size();
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < len - i - 1; j++)
        {
            if(vec[j] > v[j + 1])
                swap(vec[j], v[j + 1]);
        }
    }
}

template<typename T>
void bubble_sort2(T arr[], int len)
{
    int n = end(arr) - begin(arr);
    for(int i = 0, i < n; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] < arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

int main(int argc, char **argv)
{
    vector<int> vec = {12, 23, 32, 11, 33, 21, 43, 10};
    bubble_sort1(vec);
    bubble_sort2(vec);
    bubble_sort2(vec);
}
