#ifndef HS_H
#define HS_H

class HasPtr
{
    public:
        HasPtr(HasPtr &hs): ps(new string(*hs.ps)), i(HP.i)
        {}

        HasPtr& operator=(const HasPtr &q);

        ~HasPtr();

    private:
        string *ps;
        int i;
};

#endif
