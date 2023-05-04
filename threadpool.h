//
// Created by xuejun on 23-4-21.
//

#ifndef FEATURES_THREADPOOL_H
#define FEATURES_THREADPOOL_H
#include<iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "Task.h"

class ThreadPool
{

public:
    void Init(int num);
    void Start();
    void AddTask(Task* task);
    int Task_size();
    int Thread_size();
    Task* GetTask();
    void Stop();
    bool is_exit() { return is_exit_;}

private:

    void Run();
    std::queue<Task*> Q_Tasks;
    std::vector<std::thread*> Threads;
    int threads_num;
    bool is_exit_ = false;
};







#endif //FEATURES_THREADPOOL_H
