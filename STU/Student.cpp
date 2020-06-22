#include "Student.h"

Student::Student()
{
    Stuname = nullptr;
    Stubrith = nullptr;
    Stusex = 1;
}

Student::~Student()
{

}

Student::Student(const char * name, const char * date, const int sex, const int age)
{
    if(Stuname)
        delete[] name;

    Stuname = new char[strlen(name) + 1];
    strcpy(Stuname, name);

    if(Stubrith)
        delete[] Stubrith;
    Stubrith = new char[strlen(date) + 1];
    strcpy(Stubrith, date);

    Stusex = sex;
    Stuage = age;
}


