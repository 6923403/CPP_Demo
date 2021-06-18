#include <iostream>

/**
 * num == 66
 * 66 / 8 = 8.25 默认为8
 * 比较之后return ture了
 */

class Solution {
public:
    bool isPerfectSquare(int num) {
        int left = 0;
        int right = num;
        int mid = 0;
        while(left < right)
        {
            mid = left + (right - left) / 2;
            if((double)num / mid == mid)
            {
                std::cout << mid << std::endl;
                return true;
            }
            else if((double )num / mid < mid)
            {
                right = mid;

            }
            else
            {
                left = mid + 1;
            }

        }
        return false;
    }
};

int main()
{
    Solution a;
    int num = 66;
    bool flag = a.isPerfectSquare(num);
    std::cout << flag << std::endl;
    return 0;
}