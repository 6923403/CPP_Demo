#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
std::mutex m_mtx;

void add(int &num, int &sum)
{
    while(true){
        std::lock_guard<std::mutex> lock(m_mtx);
        if (num < 100) { //运行条件
            num += 1;
            sum += num;
        }
        else {  //退出条件
            break;
        }
    }
}

int main(int argc, const char * argv[]) {
    std::cout << "Start " << std::endl;
    
    int sum = 0;
    int num = 0;
    std::vector<std::thread> vec;
    for(int i = 0; i < 20; ++i)
    {
        std::thread t = std::thread(add, std::ref(num), std::ref(sum));
        vec.emplace_back(std::move(t)); //保存线程
    }
    std::for_each(vec.begin(), vec.end(), std::mem_fn(&std::thread::join)); //join
    std::cout << sum << std::endl;
    
    return 0;
}

//re: https://www.cnblogs.com/xudong-bupt/p/9194394.html
