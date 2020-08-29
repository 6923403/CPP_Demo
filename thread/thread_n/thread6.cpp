#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock
#include <vector>

std::mutex mtx;           // mutex for critical section
std::once_flag flag;        //定义一个once_flag类型的变量作为call_once参数，    
                                    //用std::call_once来保证多线程环境中只被调用一次
void print_block (int n, char c) {
    //unique_lock有多组构造函数, 这里std::defer_lock不设置锁状态
    std::unique_lock<std::mutex> my_lock(mtx, std::defer_lock);
    //尝试加锁, 如果加锁成功则执行
    //(适合定时执行一个job的场景, 一个线程执行就可以, 可以用更新时间戳辅助)
    if(my_lock.try_lock()){
        for (int i=0; i<n; ++i)
            std::cout << c;
        std::cout << '\n';
    }
}

void run_one(int &n){
    std::call_once(flag, [&n]{n=n+1;}); //只执行一次, 适合延迟加载; 多线程static变量情况
}

int main () {
    std::vector<std::thread> ver;
    int num = 0;
    for (auto i = 0; i < 10; ++i){
        ver.emplace_back(print_block,50,'*');  
        ver.emplace_back(run_one, std::ref(num));
  //emplace_back比push_back更好 是c++11增加的
    }

    for (auto &t : ver){
        t.join();
    }
    std::cout << num << std::endl;
    return 0;
}
