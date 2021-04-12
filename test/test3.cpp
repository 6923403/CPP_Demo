#include <iostream>
#include <string>
#include <vector>
using namespace std;


void test()
{
    string word = "aaa123d32fff411";
    int m_size = word.size();
    vector<string> vec = {"9999"};
    string tmp;
    int ret = 0;
    bool flag = false;
    for(int i = 0; i < m_size; i++)
    {
        if(word[i] <= '9' || word[i] >= '0')
        {
            tmp += word[i];
            flag = true;
        }
        else
        {
            word[i] = ' ';
d}
            if(flag)
            {
                ret++;
            }
            else
                tmp.clear();
            continue;

            vec.push_back(tmp);
            tmp.clear();
        }
    }

    for(auto s : vec)
    {
        cout << s << endl;
    }
    
    cout << ret << endl;
}

int main()
{
    test();

}
