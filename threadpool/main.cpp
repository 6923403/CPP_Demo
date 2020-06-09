#include<iostream>
#include"Thread_Pool.h"
using namespace std;
void string_out_one() {
    cout << "One!" << endl;
}
void string_out_two() {
    cout << "Two!" << endl;
}
void string_out_three() {
    cout << "Three!" << endl;
}
int main() {
    {
        Thread_Pool Pool;
        try {
            Pool.start();
        }
        catch (std::exception e)
        {
            throw e;
            cout << "线程池创建失败。" << endl;
        }
        for (int i = 0; i < 50000 ;)
        {
            if (Pool.getTaskNum() < 1000) {
                Pool.addTasks(string_out_one);
                Pool.addTasks(string_out_two);
                Pool.addTasks(string_out_three);
                std::cout << i++ << std::endl;
            }
        }
        getchar();
    }
    getchar();
    return 0;
}