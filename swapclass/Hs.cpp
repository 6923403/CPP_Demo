#include "Hs.H"

using namespace std;

void HasPtr::swap(HasPtr &lhs, HasPtr &rhs)
{
    using swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}
