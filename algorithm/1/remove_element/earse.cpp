//#27
//2020-9-19-17:00 没必要 直接erase即可
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size() - 1;
        int count = n;

        while(n > -1)
            if(nums[n] == val){
                nums.erase(nums.begin() + n);
                count--;
            }
            n--;
        }

        return  count;
    }
};

