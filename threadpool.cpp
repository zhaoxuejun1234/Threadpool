
#include <thread>
#include <stdio.h>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <future>
#include <queue>
#include "threadpool.hpp"

ThreadPool::ThreadPool(int num):threads(std::vector<std::thread>(num))
{
    
    for (int i = 0;i < threads.size(); i++)
    {
        threads[i] = std::thread(&ThreadPool::Start,this);
    }
}
ThreadPool::~ThreadPool()
{
    Stop();
}
void ThreadPool::Start()
{
    while(true)
    {
        // printf("move to this Start.\n");
        is_exit = false;
        std::unique_lock<std::mutex> u_lock(mtx);
        cv_.wait(u_lock,[this](){return (!Q_task.empty() || is_exit);});
        // printf("move to this Start2.\n");
        if(is_exit){break;}
        // printf("move to this end.\n");
        if (!Q_task.empty())
        {
            std::shared_ptr<MyTask> task = Q_task.front();
            printf("task %d infer process.\n",task->ID);
            Q_task.pop();
            task->infer();
        }
    }
}
std::shared_future<std::string> ThreadPool::TaskPush(std::shared_ptr<MyTask> task)
{
    std::unique_lock<std::mutex> u_lock(mtx);
    std::shared_future<std::string> future = task->pro.get_future();
    printf("task %d infer process.\n",task->ID);
    Q_task.push(task);
    cv_.notify_one();
    return (future);
}
void ThreadPool::Stop()
{

    is_exit = true;
    cv_.notify_all();
    // printf("move to this step1.\n");
    for(int i = 0;i < threads.size(); i++)
    {
        // printf("move to this step2.\n");
        if (threads[i].joinable())
        threads[i].join();
    }
    printf("Threads release.\n");
}