#ifndef _STUDENT_H_
#define _STUDENT_H_

//#include <vector>
#include <string>
using std::string;

class Student
{
    private:
        int Stu_id;
        string Stu_sex;
//        std::vector<string> Stu_name;
//        char Stu_name[max_size];
        char * Stu_name[256];
        char * Stu_object[10] = {"语文", "数学", "英语", "地理", "物理"};
        int grades;
        enum sexs {man = 1, woman = 2};
        
    public:
        Student();
        virtual ~Student();

        void Menu();
        void Stu_os();
        void Stu_set(const string &, const int &, const int &);
        void Stu_set(const string &, const int &);
};

#endif
