#include <iostream>
#include <memory>
using namespace std;

void test1()
{
    allocator<string> wp;
    string s;
    cin >> s;
    
    auto p = wp.allocate(10);
    auto q = p;
    while(cin >> s && s != "stop")
    {
        wp.construct(q++, s);
    }

    while(q != p)
    {
        wp.destroy(--q);
    }

    wp.deallocate(p, 10);
}

int main(int argc, char **argv)
{
    test1();
}
