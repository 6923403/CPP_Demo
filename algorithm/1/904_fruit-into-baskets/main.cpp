#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& tree) {
        // 水果编号到数量的映射
        unordered_map<int, int> veg2cnt;
        int n = tree.size();
        int res = 0;
        int index = 0;
        for(int i = 0; i < n; i++)
        {
            ++veg2cnt[tree[i]];
            while(veg2cnt.size() > 2)
            {
                int cur = tree[index];
                --veg2cnt[cur];
                if (veg2cnt[cur] <= 0)
                {
                    veg2cnt.erase(cur);
                }
                ++index;
            }
            res = max(res, i - index + 1);
        }
        return res;
    }


    int v2totalFruit(vector<int>& tree)
    {
        int slow  = 0;
        int n  = tree.size();
        vector<int>cnt(n);
        int sum = 0;
        int fast = 0;
        for(fast = 0; fast < n; fast++)
        {
            if(cnt[tree[fast]]++ == 0)
            {
                //cnt[tree[fast]]++;
                sum++;
            }
            if(sum > 2)
            {
                if(--cnt[tree[slow++]] == 0)
                {
                    //cnt[tree[slow]]--;
                    //slow++;
                    sum--;
                }
            }
        }
        return fast - slow;
    }
};

int main()
{
    vector<int> vec = {3,3,3,1,2,1,1,2,3,3,4};
    Solution a;
    int num = a.v2totalFruit(vec);
    cout << num << endl;
    return 0;
}