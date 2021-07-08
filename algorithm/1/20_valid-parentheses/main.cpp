#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace  std;

class Solution {
public:
    bool isValid(string s) {
        stack<int> st;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(') st.push(')');
            else if (s[i] == '{') st.push('}');
            else if (s[i] == '[') st.push(']');
            else if (st.empty() || st.top() != s[i]) return false;
            else st.pop(); // st.top() 与 s[i]相等，栈弹出元素
        }
        return st.empty();
    }
};

//class Solution {
//public:
//    bool isValid(string s) {
//        stack<char> st1;
//        queue<char> st2;
//        for(int i = 0; i < s.size(); i++)
//        {
//            if(s[i] == '(' || s[i] == '[' || s[i] == '{' )
//            {
//                st1.push(s[i]);
//            }
//            else
//            {
//                st2.push(s[i]);
//            }
//        }
//        bool falg = false;
//        while(!st1.empty() && !st2.empty())
//        {
//            switch(st1.top())
//            {
//                case '(':
//                {
//                    if(st2.back() != ')')
//                    {
//                        return false;
//                    }
//                    break;
//                }
//                case '[':
//                {
//                    if(st2.back() != ']')
//                    {
//                        return false;
//                    }
//                    break;
//                }
//                case '{':
//                {
//                    if(st2.back() != '}')
//                    {
//                        return false;
//                    }
//                    break;
//                }
//            }
//            st1.pop();
//            st2.pop();
//        }
//        return st1.empty() && st2.empty();
//    }
//};

int main()
{
    Solution a;
    string s;
    s = "([)]";
    s = "()[]{}";
    bool flag = a.isValid(s);
    cout << flag << endl;
    return 0;
}