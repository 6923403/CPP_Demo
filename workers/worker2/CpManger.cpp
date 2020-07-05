#include "CpManger.h"

CpManger::CpManger()
{}

CpManger::~CpManger() {

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


void CpManger::setCpinfo()
{
    std::ofstream cpout;
    cpout.open("N:\\codes\\Cplusplus\\ workers\\Commpanyinfo.txt", ios::trunc);
    if(cpout.is_open())
    {
        string tname, tadd, tem, ttel;
        cout << "公司名: ";
        cin >> tname;
        cout << "地址: ";
        cin >> tadd;
        cout << "邮箱: ";
        cin >> tem;
        cout << "电话: ";
        cin >> ttel;
        cpout << "公司名: " << tname << endl;
        cpout << "地址: " << tadd << endl;
        cpout << "邮箱: " << tem << endl;
        cpout << "电话: " << ttel << endl;

        cout << endl << "设置成功 ." << endl;
    }
    else
    {
        cout << "Can't find file ." << endl;
    }
}

void CpManger::getCpinfo()
{
    std::ifstream cpopen;
    cpopen.open("N:\\codes\\Cplusplus\\ workers\\Commpanyinfo.txt", ios::in);
    if(cpopen.is_open())
    {
        string tmp;
        while(getline(cpopen, tmp))
        {
            cout << tmp << endl;
            tmp.clear();
        }
    }
    else
    {
        cout << "Can't find Commpanyinfo.txt ." << endl;
    }
}

