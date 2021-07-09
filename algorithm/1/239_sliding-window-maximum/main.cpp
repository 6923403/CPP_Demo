#include <iostream>
#include <deque>
#include <vector>
#include <cstring>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(k==0)return {};
        vector<int>res;
        deque<size_t>window;
        /*Init K integers in the list*/
        for (size_t i = 0; i < k; i++) {
            while (!window.empty()  && nums[i] > nums[window.back()]) {
                window.pop_back();
            }
            window.push_back(i);
        }
        res.push_back(nums[window.front()]);
        /*End of initialization*/
        for (size_t i = k; i < nums.size(); i++) {
            if (!window.empty() && window.front() <= i - k) {
                window.pop_front();
            }
            while (!window.empty() && nums[i] > nums[window.back()]) {
                window.pop_back();
            }
            window.push_back(i);
            res.push_back(nums[window.front()]);
        }
        return res;
    }
};

/*
 * 超时版本
 */
//class Solution {
//public:
//    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
//        if(k <= 0)
//        {
//            return {};
//        }
//        int max_ret = 0;
//        deque<int> que;
//        vector<int> res;
//        for(int j = 0; j < k - 1; j++)
//        {
//            que.push_back(nums[j]);
//        }
//        for(int i = k - 1; i < nums.size(); i++)
//        {
//            max_ret = nums[i] - 1;
//            que.push_back(nums[i]);
//            for(int l = 0; l < k; l++)
//            {
//                max_ret = std::max(max_ret, que[l]);
//            }
//            que.pop_front();
//            res.push_back(max_ret);
//        }
//
//        return res;
//
//    }
//};

int main(int argc, char **argv)
{
    Solution a;
    vector<int>nums = {1,3,-1,-3,5,3,6,7};
    vector<int> vec;
    int k = 3;
    vec = a.maxSlidingWindow(nums, k);
    for(auto &s : vec)
    {
        cout << s << endl;
    }
    return 0;
}