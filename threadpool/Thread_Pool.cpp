#include"Thread_Pool.h"
#include<iostream>
int Task::push(Func func) {
    std::unique_lock<std::mutex> lock(mx);
    try {
        tasks.emplace(func);
    }
    catch (std::exception e)
    {
        throw e;
        return -1;
    }
    return 0;
}
int Task::getTaskNum()
{
    return tasks.size();
}
Func Task::pop() {
    std::unique_lock<std::mutex> lock(mx);
    Func temp;
    if (tasks.empty())
        return temp;
    else
    {
        temp = tasks.front();
        tasks.pop();
        return temp;
    }
}
int Thread_Pool::addTasks(Func func)
{

    int ret = tasks.push(func);
    cond.notify_one();
    return ret;
}
void Thread_Pool::start() {
    if (!IsStart) {
        IsStart = true;
        for (int i = 0; i < maxThreadNum; i++)
        {
            threads.emplace_back(new std::thread(std::bind(&Thread_Pool::run,this)));
        }

    }
}
void Thread_Pool::run()
{
    while (IsStart)
    {
        Func f;
        if (tasks.getTaskNum() == 0 && IsStart)
        {
            std::unique_lock<std::mutex> lock(tasks.mx);
            cond.wait(lock);
        }
        if (tasks.getTaskNum() != 0 && IsStart)
        {
            f = tasks.pop();
            if(f)
                f();
        }

    }
}
int Thread_Pool::getTaskNum() {
    return tasks.getTaskNum();
}
void Thread_Pool::stop() {

    IsStart = false;
    cond.notify_all();
    for (auto T : threads) {
        std::cout << "线程 " << T->get_id() << " 已停止。" << std::endl;
        T->join();
        if (T != nullptr)
        {
            delete T;
            T = nullptr;
        }
    }
    std::cout << "所有线程已停止。" << std::endl;
}
Thread_Pool::~Thread_Pool() {
    if (IsStart)
    {
        stop();
    }
}