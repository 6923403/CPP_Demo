#ifndef _CSTUDENT_H_
#define _CSTUDENT_H_

#include <iostream>
#include "Cpeople.h"

#define MAXNUM 10
using std::cout;
using std::endl;
using std::cin;

class CStudent : public Cpeople
{
    friend std::ostream& operator<<(std::ostream &out, const CStudent &s);
private:
    float m_ArrayScore[MAXNUM];

    int m_stuNo;
    int m_courseNum;
    float m_aScore;

public:
    CStudent(int age,int No,int num, char *pName):Cpeople(age,pName)
    {
        m_stuNo = No;
        m_courseNum = num;
        m_aScore = 0.0f;

        cout << "请输入学生信息" << m_pstrName << m_courseNum << "门课成绩: " << endl;
        for (int i = 0; i < m_courseNum; ++i)
            cin >> m_ArrayScore[i];
    }

    ~CStudent()
    {}

    void CaculateAverageScore()
    {
        float SUM = 0.0f;
        for (int i = 0; i < m_courseNum; ++i)
        {
            SUM += m_ArrayScore[i];
        }
        m_aScore = SUM / m_courseNum;

    }

    float Getm_aScore()
    {
        return(m_aScore);
    }

};

#endif