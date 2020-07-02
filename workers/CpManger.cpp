#include "CpManger.h"

CpManger::~CpManger() {

}

CpManger::CpManger() {

}

void CpManger::setCpinfo()
{
    std::ifstream cpopen;
    cpopen.open("Commpanyinfo.txt", ios::in | ios::binary);
    if(cpopen.is_open())
    {
        cpopen >> CpName >> CpAddress >> CpTel >> CpEmail;
    }
    else
        cout << "Open Commpanyinfo.txt failed ." << endl;
}
