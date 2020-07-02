#ifndef _WORKERS_CPMANGER_H
#define _WORKERS_CPMANGER_H

#include "Commpany.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class CpManger : public Commpany
{
public:
    CpManger();
    ~CpManger();

    void setCpinfo();

private:
    Commpany * info;

    string CpName;
    string CpAddress;
    string CpEmail;
    string CpTel;
};


#endif //_WORKERS_CPMANGER_H
