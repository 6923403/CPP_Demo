#include <iostream>
#include <string>
#include "Hs.h"
using namespace std;


HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    auto newp = new string(*rhs.ps);
    delete ps;

    ps = newp;
    i = rhs.i;
    return *this;
}
