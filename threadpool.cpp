//
// Created by xuejun on 23-4-21.
//
#include<iostream>
#include <mutex>
#include <condition_variable>
#include <future>
#include <memory>
#include <thread>
#include "threadpool.h"

std::mutex mtx;
std::condition_variable cv;
//std::promise<>


void ThreadPool::Init(int num)
{
    this->threads_num=num;
    printf("Threadpool has %d threads \n",threads_num);

}
void ThreadPool::Run()
{
//1. Get tasks from the Q_tasks; locks
//2. Task->run to get results;
//3. return results through <future>
    while (!is_exit())
    {
        Task* task = GetTask();
        auto re = task->run();
        printf("task result is %d \n",re);
    }

}
void ThreadPool::Start()
{
    std::unique_lock<std::mutex> lock(mtx);
    for (int i =0;i<threads_num;i++)
    {
       auto th = new std::thread(&ThreadPool::Run,this);
       Threads.push_back(th);
    }
//    printf("Threadpool size is %d\n",Threads.size());
}
int ThreadPool::Thread_size()
{
    std::unique_lock<std::mutex> lock(mtx);
    return Threads.size();
}
Task* ThreadPool::GetTask()
{

    std::unique_lock<std::mutex> lock(mtx);
    if (Q_Tasks.empty())
    {
        cv.wait(lock);
    }
    Task* task = Q_Tasks.front();
    Q_Tasks.pop();
    return task;

}

void ThreadPool::AddTask(Task* task)
{
    std::unique_lock<std::mutex> lock(mtx);
    Q_Tasks.push(task);
    lock.unlock();
    cv.notify_one();

}
int ThreadPool::Task_size()
{
    std::unique_lock<std::mutex> lock(mtx);
    return Q_Tasks.size();
}
void ThreadPool::Stop()
{
//    std::unique_lock<std::mutex> lock(mtx);
    is_exit_ = true;
    for (auto& th:Threads)
    {
        if (th->joinable())
        {
            th->join();
            delete th;
        }
        Threads.clear();
    }

}