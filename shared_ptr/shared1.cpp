#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

void test1()
{
    int a = 10;
    shared_ptr<int> ptra = make_shared<int>(a);
    shared_ptr<int> ptrb(ptra);

    cout << ptrb.use_count() << endl;

    int b = 20;
    int *pb = &a;

    shared_ptr<int> ptrc = make_shared<int>(b);
    ptrb = ptrc;
    pb = ptrb.get();

    cout << ptra.use_count() << endl;
    cout << ptrc.use_count() << endl;
}

int main(int argc, char **argv)
{
    test1();
}
