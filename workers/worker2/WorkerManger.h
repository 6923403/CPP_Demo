#ifndef _WORKERS_WORKERMANGER_H
#define _WORKERS_WORKERMANGER_H

#include "Commpany.h"

#include <string>
using std::string;

class WorkerManger : public Commpany
{
public:
    WorkerManger();
    ~WorkerManger();

private:
    Commpany * Worker;

};


#endif //_WORKERS_WORKERMANGER_H
