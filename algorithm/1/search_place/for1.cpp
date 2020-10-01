class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int mid = nums.size() / 2 - 1;
        int index = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            if(nums[i] >= target)
                return i;
        }

        return nums.size();
    }
};
