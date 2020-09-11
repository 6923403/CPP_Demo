#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> twosum(vector<int> &nums, const int target)
{
    vector<int> ans;
    unordered_map<int, int> hashmap;

    for(int i = 0; i < nums.size(); i++)
    {
        if(hashmap[target - nums[i]] && hashmap[target - nums[i]] != i + 1)
        {
            ans.push_back(i);
            ans.push_back(hashmap[target - nums[i]] - 1);

            return ans;
        }

        hashmap[nums[i]] = i + 1;
    }

    return ans;
}

int main()
{
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> vec;
    vec = twosum(nums, target);

    for(auto &s : vec)
    {
        cout << s << endl;
    }

    return 0;
}
