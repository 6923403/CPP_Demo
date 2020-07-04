#include <iostream>
#include "brass.h"
using namespace std;

int main(int argc, char **argv)
{
    Brass bs("bs", 381299, 4000.00);
    BrassPlus bp("bp", 38288, 5000.00, 3000.00, 3000.00);

    int c = 0;
    while(c != 100) {
    cout << "1 Deposit" << endl;
    cout << "2 DrawMoney" << endl;
    cout << "3 setAccount" << endl;
    cout << "4 Show" << endl;
    cout << "C: ";
    cin >> c;

    switch(c)
    {
        case 1: 
            bs.Deposit();
            break;
        case 2:
            bs.DrawMoney();
            break;
        case 3:
            bs.setAccount();
            break;
        case 4:
            bs.Show();
            break;

        default:
            break;
            
    }
    }

    cout << endl << endl;

    while(c != 200) {
        cout << endl;
        cout << "BrassPlus" << endl;
    cout << "1 Deposit" << endl;
    cout << "2 DrawMoney" << endl;
    cout << "3 setAccount" << endl;
    cout << "4 Show" << endl;
    cout << "C: ";
    cin >> c;
    cout << endl;

    switch(c)
    {
        case 1:
            bp.Deposit();
            break;
        case 2:
            bp.DrawMoney();
            break;
        case 3:
            bp.setAccount();
            break;
        case 4:
            bp.Show();
            break;
        default:
            break;

    }

    }

    return 0;
}
