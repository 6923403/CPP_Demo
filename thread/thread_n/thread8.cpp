#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;

atomic<int> number(0);//定义原子变量 一次只允许一个线程对其进行访问
//int number = 0;
//mutex g_lock;

int ThreadProc1()
{
    //lock_guard<mutex> loker(mutex);
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
    //lock_guard<mutex> loker(mutex);
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

    return 0;
}
