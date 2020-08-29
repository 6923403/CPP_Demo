#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <vector>

inline int func(int x)
{
    return x + 6;
}

int main()
{
    std::packaged_task<int(int)> tsk(func);
    std::future<int> fut = tsk.get_future(); //获取future绑定起来
    
    std::thread(std::move(tsk), 2).detach();//直接将task转移作为线程函数使用

    auto value = fut.get();
    std::cout << "result:" << value << std::endl;
    
    return 0;
}
