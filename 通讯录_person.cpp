//
// Created by then on 2019/10/19.
//

#include "person.h"

void manage::findname() {
    int flag = 0;
    string find_name, press;
    do
    {
        cout << "请输入被查找人姓名" << endl;
        cin >> find_name;
        for (int i = 0; i < MAX_Per; i++) {
            if (per[i].name == find_name) {
                cout << " 编号： " << per[i].listnum << endl
                     << " 姓名 : " << per[i].name << endl
                     << " 电话 : " << per[i].phonenum << endl
                     << " 邮箱 : " << per[i].mail << endl
                     << " 地址 : " << per[i].addr << endl
                     << " 分组 : " << per[i].groupname << endl;
                flag = 1;
            }

            if (flag == 0) {
                cout << " 查无此人 , 请重新查看输入内容是否正确 " << endl;
                sleep(40);
                cout << " 是否重新查找(Y/N)" << endl;
                cin >> press;
            } else { break; }
        }
    }
    while(press == "Y");


}

void manage::list_num() { //编号查询
    int flag, find_number;
    string press;
    do {

        cout << " 请输入查询编号 ： " << endl;
        cin >> find_number;
        for (int i = 0; i <= MAX_Per; i++) {
            if (per[i].listnum == find_number) {
                cout << " 编号： " << per[i].listnum << endl
                     << " 姓名 : " << per[i].name << endl
                     << " 电话 : " << per[i].phonenum << endl
                     << " 邮箱 : " << per[i].mail << endl
                     << " 地址 : " << per[i].addr << endl
                     << " 分组 : " << per[i].groupname << endl;
                flag = 1;
                return;
            }

            if (flag == 0) {
                cout << " 查无此人 , 请重新查看输入内容是否正确 " << endl;
                sleep(40);
                cout << " 是否重新查找(Y/N)" << endl;
                cin >> press;
            }
        }
    }
    while(press == "Y");

}

void manage::save() {
    ofstream outfile("f1.dat", ios::app);
    if(!outfile)
    {
        cerr << " open error! " << endl;
        exit(1);
    }

    outfile << "编号：" << ' ' << "姓名：" << ' ' << "性别：" << ' ' << "邮箱地址：" << ' ' << "联系电话："
            << ' ' << " 联系地址：" << endl;
    for(int i = 0; i <= MAX_Per; i++) {
        outfile << per[i].listnum << ' ' << per[i].name << ' ' << per[i].phonenum << ' ' << per[i].mail << ' '
                << per[i].addr << ' ' <<  per[i].groupname << endl; //向磁盘文件"f1.dat"输入数据
    }
    outfile.close();
}

void manage::look() { //查看内容
    cout << " 查看通讯录列表 " << endl;
    for(int i = 0; i < MAX_Per; i++)
    {
        cout << " 编号： " << per[i].listnum << endl
             << " 姓名 : " << per[i].name << endl
             << " 电话 : " << per[i].phonenum << endl
             << " 邮箱 : " << per[i].mail << endl
             << " 地址 : " << per[i].addr << endl
             << " 分组 : " << per[i].groupname << endl;
    }
}

void manage::add() { //添加内容
    char press;
    for(int i = 0; i < MAX_Per; i++)
    {
            cout << "请输入第 " << i << "位用户的数据 " << endl;

            cout << " 编号： "  << i << endl;
                per[i].listnum = i;
            cout  << endl << " 姓名 : ";
                cin >> per[i].name;
            cout << endl << " 电话 : ";
                cin >> per[i].phonenum;
            cout << endl << " 邮箱 : " ;
                cin >> per[i].mail;
            cout << endl << " 地址 : ";
                cin >> per[i].addr;
            cout << endl << " 分组 : ";
                cin >> per[i].groupname;

                cout << " 是否继续输入下一个用户 " ;
                cin >> press;
                if(press == 'N')
                {
                    i = 101;
                }
    }
}

void manage::modify() { //修改东西

    int find_number, flag;
    string find_name, press;

    cout << " 请输入编号或姓名(忘记就回车跳过一项) " << endl;
    cin >> find_number >>find_name;

        if(per[find_number].listnum > 0)
            cout << " 请输入要修改的内容 " << endl;
            cout << "name 1, phone 2, mail 3, addr 4, group 5" << endl;
            cin >> flag;
            switch(flag)
            {
                case 1:
                    cin >> per[find_number].name;
                    break;

                case 2:
                    cin >> per[find_number].phonenum;
                    break;

                case 3:
                    cin >> per[find_number].mail;
                    break;

                case 4:
                    cin >> per[find_number].addr;
                    break;

                case 5:
                    cin >> per[find_number].groupname;
                    break;

                default:
                cout << " 是否重新输入(Y/N) ";
                cin >> press;
                break;
            }


}

