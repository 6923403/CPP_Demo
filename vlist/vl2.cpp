#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;

void test1()
{
    int ia[] = {0, 1, 2, 3, 5, 7, 8, 13, 21, 55, 66};

    vector<int> qa(ia, ia + 1);
    list<int> kl(ia, ia + 1);
//    earse...
}

void test2()
{
    forward_list<int> s1{1, 10, 5, 8, 7, 12, 15};


}

int main()
{
    test2();
}
