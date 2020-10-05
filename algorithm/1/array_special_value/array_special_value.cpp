//1608特殊数组的特征值
//
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int specialArray(vector<int>& nums) {
        if(nums.empty())
        {
            return -1;
        }
        
        int n = nums.size();        
        sort(nums.begin(), nums.end());
        if (n <= nums[0]) return n ;

        for(int i = 1; i < n; i++)
        {
            if(nums[i] >= n - i && n - i > nums[i - 1])
                return n - i;
        }
        return -1;
    }
};

int main()
{
    vector<int> vec = {3, 6, 7, 7, 0};

    Solution ss;
    int ret =  ss.specialArray(vec);

    cout << ret << endl;

    return 0;
}
