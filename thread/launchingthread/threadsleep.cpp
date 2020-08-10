#include <iostream>
#include <chrono>
#include <thread>
 
int main()
{
    using namespace std::chrono_literals;
    std::cout << "Hello waiter\n" << std::flush;
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(2s);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    /*
     * 2000.12ms
     */
    std::cout << "Waited " << elapsed.count() << " ms\n";
}
