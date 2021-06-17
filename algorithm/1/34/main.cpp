class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left_index = -2;
        int right_index = -2;

        //寻找左右边界
        left_index = get_left(nums, target);
        right_index = get_right(nums, target);
        // 情况一
        if (left_index == -2 || right_index == -2) return {-1, -1};
        // 情况三
        if (right_index - left_index > 1) return {left_index + 1, right_index - 1};
        // 情况二
        return {-1, -1};
    }
private:
    int get_left(vector<int> nums, int target)
    {
        int m_num = nums.size();
        int left = 0;
        int right = m_num - 1;
        int mid = 0;
        int left_index = -2;
        while(left <= right)
        {
            mid = left + ((right - left) / 2);
            if(nums[mid] >= target)
            {
                right = mid - 1;
                left_index = right;
            }
            else
            {
                left = mid + 1;
            }
        }
        return left_index;
    }

    int get_right(vector<int> nums, int target)
    {
        int m_num = nums.size();
        int left = 0;
        int right = m_num - 1;
        int mid = 0;
        int right_index = -2;

        while(left <= right)
        {
            mid = left + ((right - left) / 2);
            if(nums[mid] > target)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
                right_index = left;
            }
        }

        return right_index;
    }
};