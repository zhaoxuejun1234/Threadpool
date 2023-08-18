#include "threadpool.hpp"
#include <chrono>
#include <thread>
#include <memory>
using namespace std;
int main()
{
    ThreadPool T1(3);
    this_thread::sleep_for(chrono::milliseconds(1000));
    // T1.is_exit=true;
    //此处不使用智能指针代价是巨大的，TaskPush传参采用拷贝构造，相当于又造了个对象出来，并不是一个future了，
    //导致future报错：Broken promise，本质原因是promise.set的值和promise.get_future()的不是同一个对象。
    //参数作为指针能够保证操作的对象不发生变化。
    //移动构造有相同的问题，析构了原内存，分配了新内存。
    shared_ptr<MyTask> task1(new MyTask(1));
    printf("task %d infer process.\n",task1->ID);
    shared_ptr<MyTask> task2(new MyTask(2));
    auto future = T1.TaskPush(task1);//
    // auto future2 = T1.TaskPush(task2);
    printf("task1 result is %s.\n",future.get().c_str());
    // printf("task2 result is %s.\n",future2.get().c_str());
    // T1.Stop();
}