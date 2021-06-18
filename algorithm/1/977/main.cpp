#include <iostream>
#include <vector>
using std::vector;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        //双指针 左加右减
        int n = nums.size();
        vector<int> res(n, 0);
        int i = 0;
        int j = n - 1;
        int ni = 0;
        int nj = 0;
        for(i, j; i <= j; )
        {
            ni = nums[i] * nums[i];
            nj = nums[j] * nums[j];
            std::cout << "ni = " << ni << " nj = " << nj;
            if(ni > nj)
            {
                res[--n] = ni;
                i++;
            }
            else
            {
                res[--n] = nj;
                j--;
            }
        }
        std::cout << std::endl;

        return res;
    }
};

int main()
{
    Solution a;
    vector<int> nums = {-4,-1,0,3,10};
    nums = a.sortedSquares(nums);
    for(auto &s : nums)
    {
        std::cout << s << std::endl;
    }
    return 0;
}