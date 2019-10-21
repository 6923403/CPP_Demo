//
// Created by then on 2019/10/19.
//

#ifndef UNTITLED1_PERSON_H
#define UNTITLED1_PERSON_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unistd.h>

#define MAX_Per 100
using namespace std;

class person {
    public:

        int listnum; //编号
        string mail; //邮箱
        string addr; //地址
        int phonenum;
        string name;
        string groupname;

private:
};

class manage {

public:

    void findname(); //
    void list_num();

    void save();

    void look(); //预览
    void add();

    void modify(); //修改

private:
    person per[MAX_Per];
};





#endif //UNTITLED1_PERSON_H
