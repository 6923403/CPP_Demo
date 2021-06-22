#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int len_s = s.size();
        int len_t = t.size();
        unordered_map<char, int> mp;
        for(auto &c : t)
        {
            ++mp[c];
        }
        int minStart = 0, minLen = len_s + 1;
        int left = 0, right = 0, need = len_t;
        while(right < len_s)
        {
            if(mp[s[right]] > 0)
            {
                --need;   //窗口右移，每包含一个t中的字符，need-1
            }
            --mp[s[right]];
            ++right;

            while(need == 0)    //完全覆盖子串时
            {
                if(right - left < minLen)   //此时字符被包含在[left,right)中
                {
                    minStart = left;
                    minLen = right - left;
                }
                if(++mp[s[left]] > 0)
                {
                    ++need;  //窗口左移
                }

                ++left;
            }
        }

        if(minLen != len_s + 1)
            return s.substr(minStart, minLen);
        else
            return "";
    }
};

int main()
{
    Solution str;
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string ret = "";
    ret = str.minWindow(s, t);
    cout << "ret = " << ret << endl;
    return 0;
}