#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <memory>
using namespace std;

void test1()
{

    shared_ptr<int> sh_ptr = make_shared<int>(10);

    cout << sh_ptr.use_count() << endl;

    weak_ptr<int> wp(sh_ptr);
    cout << wp.use_count() << endl;

    if(!wp.expired())
    {
        shared_ptr<int> sh_ptr2 = wp.lock();
        *sh_ptr = 100;
        cout << wp.use_count() << end;
    }
}

int main(int argc, char **argv)
{
    test1();

    return 0;
}
