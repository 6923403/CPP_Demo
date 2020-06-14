#ifndef _CPEPOPLE_H_
#define _CPEPOPLE_H_

#include <cstring>

class Cpeople
{
protected:
    int m_nAge;

public:
    char *m_pstrName;

public:
    Cpeople()
    {}
    ~Cpeople();

    Cpeople(int, char *);
    int GetAge();
    void SetAge(int age);
    void CopyPeople(Cpeople *pAnother);
};

#endif
