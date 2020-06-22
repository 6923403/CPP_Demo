#ifndef _STUSHOW_H_
#define _STUSHOW_H_

#include "Student.h"

class StuShow : public Student
{
    private:
        Student * Stu;

    public:
        StuShow()
        {}
        ~StuShow()
        {}

        void setStuinfo();
        void ShowMenu();
};

#endif
