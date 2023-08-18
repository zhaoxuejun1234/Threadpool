#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP
#include <thread>
#include <stdio.h>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <future>
#include <queue>
#include "task.hpp"
class ThreadPool
{
public:
    ThreadPool(int num);
    ~ThreadPool();
    void Start();
    std::shared_future<std::string> TaskPush(std::shared_ptr<MyTask> task);
    void Stop();
    std::atomic_bool is_exit{false};
private:
    std::mutex mtx;
    std::condition_variable cv_;
    std::vector<std::thread> threads;
    int thread_num;
    std::thread thread_worker;
    
    std::queue<std::shared_ptr<MyTask>> Q_task;

};
#endif