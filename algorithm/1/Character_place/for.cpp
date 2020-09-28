class Solution {
public:
    bool isAnagram(string s, string t) {
        int res[26] = {0};
        if(s.size() != t.size())
            return false;
        
        for(char &str : s)
        {
            res[str - 'a'] = ++res[str - 'a'];
        }

        for(char &str2 : t)
        {
            if(--res[str2 - 'a'] < 0)
            return false;
        }

        return true;
    }
};
