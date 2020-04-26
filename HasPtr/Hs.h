#ifndef HS_H
#define HS_H

#include <string>
using namespace std;
class HasPtr
{
    public:
        HasPtr(const string &s = string()): ps(new string(s)), i(0) use(new size_t(1))
        {}

        HasPtr(const HasPtr &p): ps(new string(*p.ps)), i(p.i)
        {}

        HasPtr & operator=(const HasPtr &);
        ~HasPtr();

    private:
        string *ps;
        size_t *ues;
        int i;
};
