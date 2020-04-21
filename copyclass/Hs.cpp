#include <iostream>
#include <string>

#include "Hs.h"
using namespace std;

HasPtr& HasPtr::operator(const HasPtr & Hs)
{
    a = Hs->a;
    b = Hs->b;
    c = Hs->c;
    return *this;
}

~HasPtr::HasPtr()
{
   delete Hs; 
}

