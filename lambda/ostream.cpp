#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
using namespace std;

void test1()
{
    vector<int> vec;
    istream_iterator<int> int_it(cin);
    istream_iterator<int> int_eof;
    ifstream in("afile");
    istream_iterator<string> str_it(in);
    while(int_it != int_eof)
        vec.push_back(*int_it++);
}

void test2()
{
    istream_iterator<int> in_iter(cin), eof;
    vector<int> vec(in_iter, eof);
}

void test3()
{
    ostream_iterator<int> out_iter(count, " ");
        *out_iter++ = e;
    cout << endl;
}

#if 0
void test4()
{
    istream_iterator<Sales_item> item_iter(cin), eof;
    ostream_iterator<Sales_item> out_iter(cout, "\n");
    Sales_item sum = *iter_iter++;
    while(item_iter->isbn() == sum.isbn())
    {
        if(item_iter->isbn() == sum.isbn())
            sum += *item_iter++;
        else
        {
            out_iter = sum;
            sum = *item_iter++;
        }
    }

    out_iter = sum;
}
#endif

void test5()
{
    vector<string> sk;
    ifstream in("a.txt");

    istream_iterator<string> str(in);
    istream_iterator<string> end;

    copy(str, end, back_inserter(sk));

    for(int i = 0; i < sk.size(); ++i)
    {
        cout << sk[i] << endl;
    }
}

int main(int argc, char **argv)
{
    test5();

    return 0;
}
