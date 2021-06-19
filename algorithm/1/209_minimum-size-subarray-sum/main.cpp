#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int count = 0;
        int ret = n + 1;
        int len = 0;
        for(int i = 0; i < n; i++)
        {
            count = 0;
            len = 0;
            for(int k = i; k < n; k++)
            {
                len += nums[k];
                count++;
                if(len >= target)
                {
                    cout << "len = " << len << endl;
                    ret = ret < count ? ret : count;
                    break;
                }
            }
        }

        return ret == n + 1 ? 0 : ret;

    }
};

int main()
{
    Solution a;
    vector<int> vec = {1,1,1,1,1,1,1,1};
    int target = 11;
    int ret = a.minSubArrayLen(target, vec);
    std::cout << ret << std::endl;
}