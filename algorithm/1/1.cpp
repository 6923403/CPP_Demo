#include <iostream>
#include <string>
#include <vector>


int lenstring(std::string &s)
{
    int start = 0, end = 0, len = 0, result = 0;
    size_t sz = s.size();

    while(end < sz)
    {
        char tmpc = s[end];
        for(int index = start; index < end; index++)
        {
            if(tmpc == s[index])
            {
                start = index + 1;
                len = end - start;
                break;
            }
        }

        end++;
        len++;
        result = std::max(result, len);
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
