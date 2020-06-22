#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <iostream>
#include <cstring>

class Student
{
    public:
        Student();
        virtual ~Student();
        Student(const char * name, const char * date, const int sex, const int age);

    private:
        char * Stuname;
        char * Stubrith;
        int Stuage;
        int Stusex;

};

#endif
