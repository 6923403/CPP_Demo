#include "StuMenu.h"

using std::cout;
using std::endl;
using std::cin;

void StuMenu::show()
{
    b_Stuobj(); //set obj
    b_Stuinfo(); //set stuinfo

    int choice;
    cout << "**** 选生管理系统 ****" << endl;
    cout << "**** 1. 选必修课程 ****" << endl;
    cout << "**** 2. 选选修课程 ****" << endl;
    cout << "**** 3. 查看选课情况 ****" << endl;
    cout << "**** 4. 设置课程成绩 ****" << endl;
    cout << "**** 5. 保存课程成绩 ****" << endl;
    cout << "请输入你的选择: ";
    cin >> choice;

}

StuMenu& StuMenu::build_Stuobj()
{
    char * fileName = "obj.txt";
    ifstream ifile(fileName);
    int catlog, credit;
    ocNum = 0;
    ecNum = 0;

    if(!ifile.is_open())
    {
        return *this;
    }

    while(ifile >> catlog >> cname >> credit)
    {
        switch(catlog)
        {
            case 1:
                oc[ocNum++] = new ObligatoryCourse(cname, credit);
                break;
            case 2:
                ec[ecNum++] = new ElectiveCourse(cname, credit);
                break;
        }
    }
    ifile.close();

    return *this;
}

