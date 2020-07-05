#ifndef _WORKERS_COMMPANY_H
#define _WORKERS_COMMPANY_H

#include <string>
#include <iostream>
#include <fstream>
using std::string;

class Commpany
{
public:
    Commpany();
    Commpany(const string &, const string &, const string &, const string &);
    Commpany(const unsigned int id, const string & name, unsigned int sex, unsigned int age, const string & tel, const string & email);
    virtual ~Commpany();

    virtual void setCpinfo() = 0;
    void showMenu();
    virtual void getCpinfo();
    void ExitProgam();
    void CenterControl();

private:
    /*
     * 公司名 地址 邮箱 电话
     */
    string CpName;
    string CpAddress;
    string CpEmail;
    string CpTel;

    /*
     * 工号 姓名 性别 年龄 手机号
     */
    unsigned int Workerid;
    string WorkerName;
    unsigned int WorkerSex;
    unsigned int WorkerAge;
    string WorkerTel;
    string WorkerEmail;
};

#endif //_WORKERS_COMMPANY_H
