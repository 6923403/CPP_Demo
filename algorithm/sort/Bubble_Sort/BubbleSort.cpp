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
            if(vec[j] > vec[j + 1])
                swap(vec[j], vec[j + 1]);
        }
    }

    for(auto &s : vec)
    {
        cout << s << endl;
    }
}

template<typename T>
void bubble_sort2(T &arr)
{
    int n = sizeof(arr) / sizeof(arr[0]);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }

    for(int k = 0; k < n; k++)
    {
        cout << arr[k] << endl;
    }
}

int main(int argc, char **argv)
{
    vector<int> vec = {12, 23, 32, 11, 33, 21, 43, 10};
    bubble_sort1(vec);

    cout << "222" << endl;
    int arr[] = {12, 32, 30, 21, 33, 44, 55};
    bubble_sort2(arr);

    return 0;
}
