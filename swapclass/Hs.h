#ifndef HS_H
#define HS_H

class HasPtr
{
    friend void swap(HasPtr&, HasPtr&);
};

inline void swap(HasPtr &, HasPtr &);

#endif
