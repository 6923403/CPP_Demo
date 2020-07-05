#include "Commpany.h"
#include "CpManger.h"
#include "WorkerManger.h"

enum
{ exits, cpinfo, setcpinfo,

  };

void run(int choose)
{
    Commpany * Cp = nullptr;
    Cp = new CpManger;
    Commpany * Wr = nullptr;
    //Wr = new WorkerManger;
    switch (choose)
    {
        case exits:
            cout << " 程序退出 " << endl;
            exit(-1);
            break;
        case cpinfo:
            Cp->getCpinfo();
            break;
        case setcpinfo:
            Cp->setCpinfo();
            break;

        default:
            break;
    }
}

int main(int argc, char **argv)
{
    while(true)
    {
        cout << " 0. 退出程序 " << endl;
        cout << " 1. 查看公司信息 " << endl;
        cout << " 2. 设置公司信息 " << endl;

        int choose;
        cin >> choose;
        run(choose);
        cout << endl;
    }
    return 0;
}