#include "student.h"
#include <iostream>
//#include <vector>
using namespace std;

Student::Student()
{
    //grade = 0;
    Stu_id = 0;
    Stu_sex = 1;
    name[0] = '\0';
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

void Student::Stu_os()
{
    string name;
    int sex;
    int stuid;
    cout << "请输入学生姓名: ";
    cin >> name;
    cout << endl;
    cout << "1为男 2为女" << endl;
    cout << "请输入性别(1或2): ";
    cin >> sex;
    cout << endl;
    cout << "请输入学号: ";
    cin >> stuid;
    cout << endl;

    Stu_set(name, sex, stuid);
}

void Student::Stu_set(const string &name, const int &sex, const int &stuid)
{
    Stu_name.push_back(name);
    Stu_sex = sexs(sex);
    Stu_id = stuid;
}
