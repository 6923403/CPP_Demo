#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

void v_push(shared_ptr<vector<int>> pv, int cnt)
{
    pv->push_back(cnt);
}

void v_pop(shared_ptr<vector<int>> pv)
{
    vector<int>::iterator it1 = pv->begin();
    for(it1; it1 != pv->end(); ++it1)
    {
        cout << *it1 << "  ";
    }

}

void test1()
{
    //vector<int> *pv = new shared_ptr<vector<int>>;
    shared_ptr<vector<int>> pv = make_shared<vector<int>>();


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

