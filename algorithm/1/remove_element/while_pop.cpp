class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size() - 1;

        while(n > -1)
        {
            if(val == nums[n])
            {
                nums[n] = nums[nums.size() - 1];
                nums.pop_back();
            }

            n--;
        }
        return nums.size();
    }
};
