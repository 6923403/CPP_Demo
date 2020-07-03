#include <iostream>
#include "brass.h"
using namespace std;

int main(int argc, char **argv)
{
    Brass num1;

    int c = 0;

    while(true) {
    cout << "1 Deposit" << endl;
    cout << "2 DrawMoney" << endl;
    cout << "3 setAccount" << endl;
    cout << "4 Show" << endl;
    cout << "C: ";
    cin >> c;

    switch(c)
    {
        case 1: 
            num1.Deposit();
            break;
        case 2:
            num1.DrawMoney();
            break;
        case 3:
            num1.setAccount();
            break;
        case 4:
            num1.Show();
            break;

        default:
            break;
            
    }
    }

    return 0;
}
