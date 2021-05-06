#include <iostream>

int F[] = {0,1,1,2,3,5,8,13,21};

int test(int a[], int n, const int key) {
    int low, high, mid, i, k;
    low = 1;
    high = n;
    k = 0;
    while (n > F[k] - 1) {
        k++;
    }

    /*
     * 将不满的数值补全
     */
    for (i = n; i < F[k] - 1; i++) {
        a[i] = a[n];
    }

    while (low <= high)
    {
        mid = low + F[k - 1] -1;
        if(a[mid] > key)
        {
            high = mid - 1;
            k = k - 1;
        }
        else if(a[mid] < key)
        {
            low = mid + 1;
            k = k - 2;
        }
        else
        {
            if(mid <= n)
            {
                return mid;
            } else
            {
                return n;
            }
        }

    }

}

int main(int argc, char** argv)
{
    int a[20] = {0,1,16,24,35,47,59,62,73,88,99};
    const int key = 59;
    int n = 10;
    int num = test(a, n, key);
    std::cout << "num = " << num << std::endl;

    return 0;
}