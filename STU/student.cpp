#include "student.h"
#include <iostream>

using std::cout;
using std::endl;

Student::Student()
{
    grade = 0;
    name[0] = '\0';
    sex = sexs(1);
}

Student::~Student()
{

}

void Student::Menu()
{
    cout << " *     信息管理      " << endl;
    cout << " * 1. 设置学生信息 " << endl;
    cout << " * 2. 查看学生信息 " << endl;
    cout << " * 3. 修改学生信息 " << endl;
    cout << " * 4. 查看学生排名 " << endl;
    cout << " * 5. 其他 " << endl;
    cout << " * 6. 程序退出 " << endl;
}
