#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<chrono>


std::mutex g_mu;
std::condition_variable g_vc;
bool g_ready = false;

void dispaly_id(int id)
{
    std::unique_lock<std::mutex> lck(g_mu);
    g_vc.wait(lck, []() {return g_ready; });   //线程阻塞，直到第二个参数返回值为真

    std::cout << "id:" << id << std::endl;
}

void ready()
{
    std::unique_lock<std::mutex> lck(g_mu);
    g_ready = true;
    g_vc.notify_all();    //唤醒所有的等待线程
}

int main()
{
    std::thread t[8];
    for (int i = 0; i < 8; i++)
    {
        t[i] = std::thread(dispaly_id, i);
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "all thread lock......" << std::endl;
    
    ready();

    for (auto & th : t) 
        th.join();

 //   getchar();

    return 0;
}
