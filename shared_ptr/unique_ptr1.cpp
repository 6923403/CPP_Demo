#include <iostream>
#include <memory>
#include <vector>
using namespace std;

void test1()
{
    unique_ptr<int> uptr(new int(10));
    
    cout << *uptr << endl;

    //move owership
    unique_ptr<int> uptr2 = move(uptr);

    uptr2.release();

}

int main(int argc, char **argv)
{
    test1();
}

