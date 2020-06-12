#ifndef _STUDENT_H_
#define _STUDENT_H_

class Student
{
    private:
        int grade;
        int sex;
        char name[3];
        enum sexs {man = 1, woman = 2};
        
    public:
        Student();
        virtual ~Student();
        void Menu();
};

class Control : public Student
{
    public:
        Control();
        ~Control();

        void changestu_info();
        void changestu_grade();
};

#endif
