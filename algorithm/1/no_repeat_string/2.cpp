#include <iostream>
#include <string>
#include <vector>


int lenstring(std::string &s)
{
    std::vector<int> vec(128, 0);

    int n = 0, i = 0;

    for(int j = 0; j < s.size(); j++)
    {
        i = std::max(i, vec[s[j]]);
        vec[s[j]] = j + 1;
        n = std::max(n, j - i + 1);
    }

    return n;
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
