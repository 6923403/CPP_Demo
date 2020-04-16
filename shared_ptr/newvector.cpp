#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

void v_push(vector<int> *pv, int cnt)
{
    pv->push_back(cnt);
}

void v_pop(vector<int> *pv)
{
    vector<int>::iterator it1 = pv->begin();
    for(it1; it1 != pv->end(); ++it1)
    {
        cout << *it1 << "  ";
    }

    delete pv;

    pv = nullptr;
}

void test1()
{
    vector<int> *pv = new vector<int>;

    int cnt;
    while(cin >> cnt && cnt != 666)
    {
        v_push(pv, cnt);
    }
    v_pop(pv);
}


int main(int argc, char **argv)
{
    test1();

    return 0;
}

