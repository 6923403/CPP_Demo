#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

void test1()
{
    vector<int> deq{1, 2, 3, 4, 5, 6, 7};
    list<vector<int> > sa;
}

bool find(vector<int>::iterator it1, vector<int>::iterator it2, int k)
{
    for(it1; it1 != it2; it1++)
    {
        if(*it1 == k)
            return true;
    }

    return false;
}

void test2()
{
    vector<int> seq{1, 2, 3, 4, 6, 8, 33};
    auto it1 = seq.begin();
    auto it2 = seq.end();

    int s;
    cin >> s;
    if(find(it1, it2 ,s))
        cout << "True" << endl;
    else 
        cout << "False" << endl;
}

void test3()
{
    list<int> s;
    vector<double> ki(s.begin(), s.end());


}

void test4()
{
    list<char *> k1(10, "s");
    vector<string> kn;
    kn.assign(k1.begin(), k1.end());
    for(auto s : kn)
    {
        cout << s << endl;
    }
}

bool compare(vector<int> &k1, vector<int> &k2)
{
    for(auto q1 : k1)
    {
        for(auto q2 : k2)
        {
            if(q1 == q2)
                break;
            else if(q1 > q2)
            {
                cout << "1" << endl;
                return true;
            }
            else
            {
                cout << "2" << endl;
                return false;
            }
        }
    }

    return true;
}

void test5()
{
    vector<int> s1 = {1,243,45,12,32,21,31,1};
    vector<int> s2 = {1,23,123,123,123,5,2,12,3,};

    compare(s1, s2);
}

int main(int argc, char **argv)
{
//    test1();
//    test2();
//    test3();
//    test4();
    test5();
}
