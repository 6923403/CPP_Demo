#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int> twosum(vector<int> &nums, int target)
{
    vector<int> ans;
    vector<int> temp;
    temp = nums;

    cout << "start twosum" << endl;
    int n = nums.size();
    sort(temp.begin(), temp.end());
    int i = 0, j = n - 1;
    while(i < j)
    {
        if(temp[i] + temp[j] > target) 
            j--;
        else if(temp[i] + temp[j] < target)
            i++;
        else
            break;
    }
    cout << i << endl;
    cout << j << endl;

    cout << "start3" << endl;
    int flag = 0;
    for(int t1 = 0; t1 < n; t1++)
    {
        switch(flag)
        {
            case 0:
                if(nums[t1] == temp[i])
                {
                    ans.push_back(t1);
                    t1 = -1;
                    flag++;
                }
                break;
            case 1:
                if(nums[t1] == temp[j])
                {
                    ans.push_back(t1);
                    return ans;
                }
                break;
            default:
                t1 = n;
                break;
        }
    }
    return ans;
}

int main()
{
    vector<int> sum = {2, 7, 11, 15};
    int target = 9;
    vector<int> vec;
    cout << "start" << endl;
    vec = twosum(sum, target);
    cout << "end" << endl;

    for(auto &s : vec)
    {
        cout << s << endl;
    }

    return 0;
}
