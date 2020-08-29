#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;

int number = 0;
mutex g_lock;

int ThreadProc1()
{
    lock_guard<mutex> loker(g_lock);
    for (int i = 0; i < 100; i++)
    {
        ++number;
        cout << "thread 1 :" << number << endl;
        
    }
    //this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}

int ThreadProc2()
{
    lock_guard<mutex> loker(g_lock);
    for (int i = 0; i < 100; i++)
    {
        --number;
        cout << "thread 2 :" << number << endl;
        //this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;
}

int main()
{
    thread t1(ThreadProc1);
    thread t2(ThreadProc2);

    t1.detach();
    t2.detach();

    getchar();
    return 0;
}
