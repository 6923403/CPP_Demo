#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <vector>

void disPlay(std::future<int>& value)
{
    std::cout << "wait some times......" << std::endl;
    auto result = value.get();    //没有获取到值会阻塞等待获取
    std::cout << "Value:" << result << std::endl;
}


int main()
{
    std::promise<int> promise;    
    std::future<int> value = promise.get_future(); //将promise与future绑定
    
    std::thread t1(disPlay, std::ref(value));  //创建线程并且函数传参，ref()是传一个引用
    std::this_thread::sleep_for(std::chrono::seconds(1)); //线程延时1秒

    //给线程传值进去
    promise.set_value(15);
    t1.join();
    
    return 0;
}
