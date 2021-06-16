#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        return search(nums, target, 0, nums.size() - 1);
    }
private:
    int search(vector<int> &nums, int target, int left, int right)
    {
        if(left > right)
        {
            return - 1;
        }

        int mid = left + ((right - left) / 2);

        if(nums[mid] == target)
        {
            return mid;
        }
        return nums[mid] < target ? search(nums, target, mid + 1, right) :
               search(nums, target, left, mid - 1);
    }
};

int main()
{
    vector<int> nums = {-1,0,3,5,9,12};
    Solution a;
    std::cout << a.search(nums, 9) << std::endl;
}