#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <sys/time.h>
#include "person.h"

using namespace std;

int64_t getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 100;

}

int main(int argc,char **argv)
{
    cout << getCurrentTime() << endl;

    cout<<endl<<endl;
    cout<<"            *            *** 通讯录 - 🌍 🏇🎉🐮***          *"<<endl;
    cout<<"            *                                        *"<<endl;
    cout<<"            *    1.新增通讯录      4.编号查询详细信息     *"<<endl;
    cout<<"            *    2.修改通讯录      5.姓名查询详细信息     *"<<endl;
    cout<<"            *    3.预览信息        6.保存数据           *"<<endl;
    cout<<"            *               0.退出                    *"<<endl;
    cout<<"            * * * * * * * * * * * * * * * * * * * * **"<<endl;

    manage s1;
    int flag;
    while(true) {
        cout << " 输入你的操作字符 " << endl;

        cin >> flag;

        switch (flag) {
            case 1:
                s1.add();
                break;

            case 2:
                s1.modify();
                break;
            case 3:
                s1.look();
                break;

            case 4:
                s1.list_num();
                break;

            case 5:
                s1.findname();
                break;

            case 6:
                s1.save();
                break;

            case 0:
                exit(1);
                break;

            default:
                cout << " 输入有误，请重新输入 " << endl;
                break;

        }
    }


}
