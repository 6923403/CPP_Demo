#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if(haystack.empty())
        {
            return 0;
        }
        int l = 0, r = 0;
        for(l, r; l < haystack.size(); l++)
        {
            if(haystack[l] == needle[0])
            {
                bool flag = true;
                int i = 1;
                r = l + 1;
                while(i < needle.size())
                {
                    if(haystack[r] == needle[i])
                    {
                        flag = true;
                        r++;
                    }
                    else
                    {
                        flag = false;
                        break;
                    }
                    i++;
                }

                if(flag == true)
                {
                    return l;
                }
            }
        }

        return -1;
    }
};

int main()
{
    Solution a;
    string haystack = "a", needle = "a";
    int ret = a.strStr(haystack, needle);
    cout << ret << endl;
    return 0;
}