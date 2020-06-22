#include "StuShow.h"

#include <iostream>

using namespace std;

void StuShow::setStuinfo()
{
    char * name;
    char * date;
    int sex;
    cout << "Student name: ";
    cin >> name;
    cout << endl;
    cout << "Student birthDate: ";
    cin >> date;
    cout << endl;
    cout << "Studnet sex: ";
    cin >> sex;
    cout << endl;
    Stu = new Student(name, date, sex);
}

void StuShow::ShowMenu()
{
    setStuinfo();
    int choice;

    cout << "**** Stuednt Manager OS ****" << endl;
    cout << "**** 1. Set Objects ****" << endl;
    cout << "**** 2. Show Objects ****" << endl;
    cout << "**** 3. Set Objects Grades ****" << endl;
    cout << "**** 4. Save Student info to file ****" << endl;
    cout << "**** 5. Exit ****" << endl;
    cout << "Input your thought: ";
    //cin >> choice;
}
