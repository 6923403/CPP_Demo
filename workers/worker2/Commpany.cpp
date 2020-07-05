#include "Commpany.h"
#include "CpManger.h"
using namespace std;

Commpany::Commpany()
{

}

Commpany::~Commpany()
{

}

void Commpany::showMenu()
{
        cout << " ****  企业职工系统 ****" << endl;
        cout << " 1. 工人信息 " << endl;
        cout << " 2. 公司信息 " << endl;
        cout << " **** 10. 退出程序 ****" << endl;

        CenterControl();
}

void Commpany::getCpinfo()
{
    std::ifstream cpopen;
    cpopen.open("N:\\codes\\Cplusplus\\ workers\\Commpanyinfo.txt", ios::in);
    if(cpopen.is_open())
    {
        cpopen >> CpName >> CpAddress >> CpTel >> CpEmail;
        cout << endl;
        cout << "公司名称: " << CpName << endl;
        cout << "公司地址: " << CpAddress << endl;
        cout << "联系电话: " << CpTel << endl;
        cout << "电子邮件: " << CpEmail << endl;
        cout << endl;
    }
    else
    {
        cout << "Can't find Commpanyinfo.txt ." << endl;
    }
}



enum Con
{
    other,
    Workerinfo,
    enumTwo,
    enumThree,
    Cpinfo,
    setCpinfo,
    Exit = 10,
};

void Commpany::CenterControl() //总控
{
    cout << "请输入您的选择: ";
    int Ctmp;
    cin >> Ctmp;
    switch(Ctmp)
    {
        case Con::Workerinfo: //工人信息
            break;
        case Con::Cpinfo: //公司信息
            break;
        case Con::setCpinfo:
            break;
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