#include "Cpeople.h"

Cpeople::Cpeople(int age, char *name)
{
    m_nAge = age;
    m_pstrName = new char[strlen(name) + 1];
    strcpy(m_pstrName, name);
}
Cpeople::~Cpeople()
{
    if (m_pstrName != NULL)
        delete[]m_pstrName;
}
int Cpeople::GetAge()
{
    return m_nAge;
}

void Cpeople::SetAge(int age)
{
    m_nAge = age;
}

// 将另一个CPeople对象的成员变量值拷贝到当前CPeople对象对应的成员变量中
void Cpeople::CopyPeople(Cpeople *pAnother)
{
    m_nAge = pAnother->m_nAge;
    strcpy(m_pstrName, pAnother->m_pstrName);

    //**************请考生完成该成员函数**************
}