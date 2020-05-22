#include <iostream>
#include "mytime.h"

int main(int argc, char **argv)
{
    using namespace std;
    Time planning;
    Time coding(2, 40);
    Time total;
    Time fixing(5, 55);

    cout << "Planning time = ";
    planning.show();

    cout << "coding time = ";
    coding.show();

    cout << "fixing time = ";
    fixing.show();
    
    //total = coding.Sum(fixing);
    total = coding + fixing;
    total.show();

    return 0;
}

