#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <vector>
#include <string>
using std::string;

class Student
{
    private:
        int Stu_id;
        int Stu_sex;
        std::vector<string> Stu_name;
        char name[3];
        enum sexs {man = 1, woman = 2};
        
    public:
        Student();
        virtual ~Student();

        void Menu();
        void Stu_os();
        void Stu_set(const string &, const int &, const int &);
};

class Control : public Student
{
    public:
        Control();
        ~Control();

        void changeStu_info();
        void changeStu_grade();
};

#endif
