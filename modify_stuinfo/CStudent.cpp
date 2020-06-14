#include "CStudent.h"
using std::ostream;
ostream &operator<<(ostream &out, const CStudent &s)
{
    out << "学生姓名：" << s.m_pstrName << "，学号：" << s.m_stuNo << ".成绩：" << endl;
    for (int i = 0; i < s.m_courseNum; ++i)
    {
        out << s.m_ArrayScore[i] << endl;
    }
    out << "平均成绩=" << s.m_aScore << endl << endl;
    return out;
}
