#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findN(vector<int> &nums)
{
    for(int i = 0; i < nums.size(); i ++)
        while(nums[i] != i)
            if(nums[i] == nums[nums[i]]) return nums[i];
                else swap(nums[i], nums[nums[i]]);
    return -1;
}

int main()
{
    vector<int> nums = {2, 3, 1, 0, 2, 5, 3};
    int q = findN(nums);

    cout << q << endl;

    return 0;
}
