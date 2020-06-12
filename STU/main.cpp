#include <iostream>
#include "student.h"
#include "stushow.h"

int main(int argc, char **argv)
{
    using namespace std;

    Student Stu;
    Stu.Menu();
    int k = 0;
    cout << "want you do? : ";
    while(cin >> k)
    {
        /*
         * 1 set stu
         * 2 showstu
         * 3 change stuinfo
         * 4 show sort
         */
        switch(k)
        {
            case 1: 
                break;
            case 6:
                exit(-1);
            default: 
                cout << "restart input" << endl;
                break;
        }
        cout << "want you do? : ";
    }

    return 0;
}
