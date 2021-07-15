#include <iostream>
#include <string>
#include <set>
using namespace std;

class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();
        if(n == 3 && s[0] != s[2]) return 0;
        set<char> Characters;
        int res = 0;
        // 枚举起点
        for(int i = 0; i <= n - 2; )
        {
            // 枚举终点，从后面找，可以得到最长的一段
            int j = n - 1;
            while(j >= i + 2  && s[j] != s[i]) j --;
            // 找到了，中间不重复的字符数就是满足题目的回文子串的个数
            if(j >= i + 2)
            {
                Characters.insert(s[i]); // 该字母为首尾的回文串已经用过了，去重
                set<char> S;
                for(int k = i + 1; k < j; k ++) S.insert(s[k]);
                res += S.size();
            }
            // 枚举下一个起点
            int k = i + 1;
            while(k < n && Characters.count(s[k])) k ++;
            i = k ;
        }

        return res;
    }
};


int main()
{
    string s = "bbcbaba";
    Solution a;
    int n = a.countPalindromicSubsequence(s);
    cout << n << endl;
    return 0;
}