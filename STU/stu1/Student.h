#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <fstream>
#include <iostream>
#include <ctime>

struct StuNode
{
    int num;
    int math, eng, chinese;
    int sum;
    StuNode * next;
};

class Student
{
public:
    Student();
    ~Student();

    void CreateStuinfo();
    void CreateStuinfo(StuNode *) const;
    void ShowMenu();
    void Selectcase();
    void setFileStu();
    void saveFileStu();
    void StuInsert(int, int, int, int);
    void StuDelete();
    void ShowInfo();
    void ShowInfo(StuNode * s) const;
    void StuFind();
    void StuInfoModify();

private:
    StuNode * StuListHead;
};

#endif //STU1_STUDENT_H
