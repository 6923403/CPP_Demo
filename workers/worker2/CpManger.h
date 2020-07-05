#ifndef _WORKERS_CPMANGER_H
#define _WORKERS_CPMANGER_H

#include "Commpany.h"
using namespace std;

class CpManger : public Commpany {
public:
    CpManger();
    ~CpManger();

    virtual void setCpinfo();
    virtual void getCpinfo();

private:

};


#endif //_WORKERS_CPMANGER_H
