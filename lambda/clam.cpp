#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

void test1()
{
    size_t v1 = 42;
    auto f = [v1] ()mutable {return ++v1;};
    v1 = 0;
    auto j = f();
    cout << j << endl;
}

void test2()
{
    size_t v2 = 42;
    auto f2 = [&v2]{
        return ++v2;
    };
    v2 = 0;
    auto s = f2();
    cout << s << endl;

}

void test3()
{
    vector<int> v1 = {12, 55, 66, 55, 112, 223, 54, 11, 78};
    transform(v1.begin(), v1.end(), v1.begin(), [](int i)
            {
                return i < 0 ? -i : i;
            });

    for(const auto s : v1)
        cout << s << "   ";
}

void test4()
{
    vector<int> v1 = {12, 55, 66, 55, 112, 223, 54, 11, 78};
    transform(v1.begin(), v1.end(), v1.begin(),
            [](int i) -> int
            {
                if(i < 0)
                    return -1;
                else
                    return i;
            });
}

int main(int argc, char **argv)
{
    test4();

    return 0;
}
