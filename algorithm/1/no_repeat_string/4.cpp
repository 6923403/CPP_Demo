#include <iostream>
#include <string>
#include <vector>
#include <map>


int lenstring(std::string &s)
{
    //s[start,end) 前面包含 后面不包含
    int start(0), end(0), length(0), result(0);
    int sSize = int(s.size());
    std::vector<int> vec(128, -1);
    while (end < sSize)
    {
        char tmpChar = s[end];
        //仅当s[start,end) 中存在s[end]时更新start
        if (vec[int(tmpChar)] >= start)
        {
            start = vec[int(tmpChar)] + 1;
            length = end - start;
        }
        vec[int(tmpChar)] = end;

        end++;
        length++;
        result = std::max(result, length);
    }
    return result;
}

int main()
{
    std::string s1 = "bbbbb";
    std::string s2 = "abcabcbb";

    int n1 = 0, n2 = 0;
    n1 = lenstring(s1);
    n2 = lenstring(s2);

    std::cout << "n1 = " << n1 << std::endl;
    std::cout << "n2 = " << n2 << std::endl;

    return 0;
}
