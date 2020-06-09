#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_
#include<thread>
#include<queue>
#include<mutex>
#include<atomic>
#include<vector>
#include<condition_variable>
#include <functional>

typedef std::function<void()> Func;//定义线程执行函数类型，方便后面编码使用。
//任务类
class Task {
public:
 Task() {}
 ~Task() {}
 int push(Func func);//添加任务;
 int getTaskNum();//获得当前队列中的任务数;
 Func pop();//取出待执行的任务;
public:
 std::mutex mx;//锁;
private:

 std::queue<Func> tasks;//任务队列
};
//线程池类
class Thread_Pool {
public:
 Thread_Pool() :IsStart(false) {}
 ~Thread_Pool();
 int addTasks(Func tasks);//添加任务;
 void start();//开启线程池;
 void stop();//关闭线程池;
 void run();//线程工作函数;
 int getTaskNum();//获得当前队列中的任务数;
private:
 static const int maxThreadNum = 3;//最大线程数为3;

 std::condition_variable cond;//条件量;
 std::vector<std::thread*> threads;//线程向量;
 std::atomic<bool> IsStart;//原子变量，判断线程池是否运行;
 Task tasks;//任务变量;
};
#endif