#ifndef EM_H
#define EM_H

#include <string>
using namespace std;

class Employee
{
    public:
        Employee();
        void setperson();
        void showperson();

    private:
        string name;
        int cardID;
};

#endif
