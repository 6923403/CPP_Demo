#ifndef _WORKERS_COMMPANY_H
#define _WORKERS_COMMPANY_H

#include <string>
using std::string;

class Commpany
{
public:
    Commpany();
    virtual ~Commpany();

    void showMenu();
    void CenterControl();
    void ExitProgam();
private:
    int Ctmp;
    //CpManger * setCp;

};


#endif //_WORKERS_COMMPANY_H
