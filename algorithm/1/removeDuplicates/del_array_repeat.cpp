#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty())
        return 0;

        int sz = nums.size();
        
        int count = 0;
        for(int i = 0; i < (sz - 1); i++)
        {
            if(nums[i] != nums[i + 1])
            {
                nums[count + 1] = nums[i + 1];
                count++;
            }
        }

        return count + 1;
    }
};

int main()
{
    Solution aw;
    vector<int> vec = {1, 1};
    
    int sz = 0;
    sz = aw.removeDuplicates(vec);
    cout << sz << endl;

    for(int i = 0; i < sz; i++)
    {
        cout << vec[i];
    }


    return 0;
}
