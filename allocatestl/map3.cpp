#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

bool cpmpareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

void test1()
{

}

int main(int argc, char **argv)
{
    test1();
}
