#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;
using namespace std;


/**
 * 1.普通函数指针
 * 2.Lambda函数
 * 3.Functors
 * 4.非静态成员函数
 * 5.静态成员函数
 */

using ull = unsigned long long;
ull OddSum = 0;
ull EvenSum = 0;

void findEven(ull start, ull end) {
    for (ull i = start; i <= end; ++i)
        if ((i & 1) == 0)
            EvenSum += i;
}

void findOdd(ull start, ull end) {
    for (ull i = start; i <= end; ++i)
        if ((i & 1) == 1)
            OddSum += i;
}

int main() {

    std::cout << "aaa" << std::endl;
    ull start = 0, end = 1900000000;


    auto startTime = high_resolution_clock::now();
    std::thread t1(findEven,start,end);
    std::thread t2(findOdd,start,end);

    /*
     * join()就是阻塞线程
     * 阻塞的目的就是让Main主线程等待一下创建的线程，免得我函数还在跑，程序就直接结束了。
     *
     * detach()将线程与线程对象分离
     */
    t1.join();
    t2.join();

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "OddSum : " << OddSum << endl;
    cout << "EvenSum: " << EvenSum << endl;
    cout << "Sec: " << duration.count() / 1000000 << endl;
    return 0;
}
