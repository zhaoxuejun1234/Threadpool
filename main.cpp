//
// Created by xuejun on 23-4-21.
//
#include <iostream>
#include <thread>
#include "threadpool.h"
using namespace  std;

int main()
{
    ThreadPool pool;
    pool.Init(10);
    pool.Start();

    MyTask task1;
    task1.name = "task1";
    pool.AddTask(&task1);
    MyTask task2;
    task2.name = "task2";
    pool.AddTask(&task2);
    this_thread::sleep_for(chrono::microseconds(3000));

    printf("Q_tasks size is %d \n",pool.Task_size());
    pool.Stop();
    return 0;
}