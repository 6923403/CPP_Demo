#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <future>
#include <vector>

int main()
{
    std::future<int> fut = std::async(std::launch::async, []() {
        return 9;
    });
    
    std::cout << "result:" << fut.get() << std::endl;

    return 0;
}
