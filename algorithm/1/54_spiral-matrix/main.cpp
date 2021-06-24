#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector <int> ans;
        if(matrix.empty()) return ans; //若数组为空，直接返回答案
        int up = 0; //赋值上下左右边界
        int d = matrix.size() - 1;
        int left = 0;
        int r = matrix[0].size() - 1;
        while(true)
        {
            for(int i = left; i <= r; ++i) ans.push_back(matrix[up][i]); //向右移动直到最右
            if(++ up > d) break; //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同
            for(int i = up; i <= d; ++i) ans.push_back(matrix[i][r]); //向下
            if(-- r < left) break; //重新设定有边界
            for(int i = r; i >= left; --i) ans.push_back(matrix[d][i]); //向左
            if(-- d < up) break; //重新设定下边界
            for(int i = d; i >= up; --i) ans.push_back(matrix[i][left]); //向上
            if(++left > r) break; //重新设定左边界
        }
        return ans;
    }
};

int main()
{
    vector<int> ret = {};
    vector<vector<int>> nums = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}};
    vector<vector<int>> nums2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> nums3 = {{3}, {2}};
    Solution a;
    ret = a.spiralOrder(nums);
    for(auto &s : ret)
    {
        cout << s << " ";
    }
    cout << endl;
    return 0;
}