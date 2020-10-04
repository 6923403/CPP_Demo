#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    Solution() {};
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = n - 1; //定义target在左闭右闭的区间里，[left, right] 
        int mid = 0;

        while (left <= right)
        {
            mid = (right - left / 2) + left;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] > target)
                right = mid - 1;
            else if(nums[mid] < target)
                left = mid + 1;
        }

        return right + 1;
    }
};

int main()
{
    vector<int> nums = {1, 2, 5, 6, 8};
    int target = 0;
    cin >> target;
    cout << endl;
    Solution sk;

    int res;
    res = sk.searchInsert(nums, target);
    cout << "res = " << res << endl;

    return 0;
}
