#include "Commpany.h"
#include <iostream>
using namespace std;

Commpany::Commpany()
{
    Ctmp = 10;
}

Commpany::~Commpany()
{

}

void Commpany::showMenu() //init
{
    cout << " ****  企业职工系统 ****" << endl;
    cout << " **** 1. 添加新员工 ****" << endl;
    cout << " **** 2. 导入员工列表 ****" << endl;
    cout << " **** 3. 员工工作分配 ****" << endl;
    cout << " **** 4. 公司信息展示 ****" << endl;
    cout << " **** 10. 退出程序 ****" << endl;

    CenterControl();
}


enum Con
{
    Workerinfo,
    enumTwo,
    enumThree,
    Cpinfo,
    Exit = 10,
};

void Commpany::CenterControl() //总控
{
    cout << "请输入您的选择: ";
    cin >> Ctmp;
    switch(Ctmp)
    {
        case Con::Workerinfo:
            break;
        case Con::Cpinfo:
           // CpManger();
        case Con::Exit:
            ExitProgam();
        default:
            cout << "选项错误，重新输入" << endl;
            CenterControl();
            break;
    }

}


void Commpany::ExitProgam() //退出程序
{
    cout << "程序退出 ." << endl;
    exit(-1);
}