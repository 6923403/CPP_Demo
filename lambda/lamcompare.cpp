#include <iostream>
using namespace std;

int all_num = 0;

int main()
{
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;

    cout << "lambda1: \n";

    auto lambda1 = [=]{
        all_num = 10;
        cout << num1 << " " << num2 << " " << num3 << " \n"; 
        cout << all_num << endl;
    };
    lambda1();
    cout << all_num << endl << endl;

    auto lambda2 = [&]{
        all_num = 100;
        num1 = 5;
        num2 = 10;
        num3 = 15;
        cout << num1 << " " << num2 << " " << num3 << " \n"; 
        cout << all_num << endl;
    };
    lambda2();
    cout << all_num << endl;

    return 0;
}


