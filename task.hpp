#ifndef TASK_HPP
#define TASK_HPP
#include<stdio.h>
#include <string>
#include <future>
#include <memory>
class Task
{
public:
    virtual void infer()=0;

};
class MyTask:public Task
{
public:
    // std::shared_ptr<std::promise<std::string>> pro;
    std::promise<std::string> pro;
    int ID;
    MyTask();
    MyTask(int num);
    MyTask(const MyTask&);
    MyTask(const MyTask&&);
    virtual ~MyTask();
    virtual void infer() override;
};
#endif