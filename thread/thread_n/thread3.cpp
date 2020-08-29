//#include<windows.h>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

int number = 1;

int ThreadProc1()
{
    while (number < 100)
    {
        cout << "thread 1 :" << number << endl;
        ++number;
       this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}

int ThreadProc2()
{
    while (number < 100)
    {
        cout << "thread 2 :" << number << endl;
        ++number;
        this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}

int main()
{
    thread t1(ThreadProc1);
    thread t2(ThreadProc2);

    t1.join();
    t2.join();

    system("pause");
    return 0;
}
