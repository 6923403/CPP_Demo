#ifndef _STUMENU_H_
#define _STUMENU_H_

#include <iostream>
#include <fstream>

#include "Student.h"
#include "ObligatoryCourse.h"
#include "ElectiveCourse.h"
#include "Date.h"

#define Max_size 256

class StuMenu
{
    public:
        void show();
        StuMenu& build_Stuobj();
        StuMenu& build_Stuinfo();

    private:
        Student * stu;
        StuMenu * oc[Max_size];
        StuMenu * ec[Max_size];

        /*
         * oc必修课程实际数量
         * ec选修课程实际数量
         */
        int ocNum;
        int ecNum;
};

#endif
