#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Sales_data
{
    public:
        Sales_data();
        Sales_data(int q):book(q)
        {

        }

        int show()
        {
            return book;
        }

    private:
        int book;
};

bool compareisbn(Sales_data q1, Sales_data q2)
{
    return q1.show() < q2.show();
}

void test1()
{
    Sales_data a1(99);
    Sales_data a2(100);
    Sales_data a3(20);
    Sales_data a4(111);

    vector<int> ss;
    ss.push_back(a1.show());
    ss.push_back(a2.show());
    ss.push_back(a3.show());
    ss.push_back(a4.show());

    stable_sort(ss.begin(), ss.end(), compareisbn);

    for(auto s : ss)
        cout << s << "   " << endl;

}

bool compares(string &w)
{
    if(w.size() > 5)
        return true;
    else
        return false;
}

void test2()
{
    vector<string> ww = {"asd", "qweqwe", "asdasd", "dbf", "xcved", "qwerssr"};

    auto k = partition(ww.begin(), ww.end(), compares);
    cout << *k << endl;

    for(const auto s : ww)
        cout << s << "   " << endl;
}

int main(int argc, char **argv)
{
    test2();
}
