
#include<stdio.h>
#include <string>
#include <future>
#include "task.hpp"
void MyTask::infer() 
{
    // printf("task %d infer process.\n",ID);
    pro.set_value(std::to_string(ID)+" Finished.");
    printf("Infer done.\n");
}
MyTask::MyTask(){printf("Construct.\n");}
MyTask::MyTask(int num):ID(num){printf("Construct with parama.\n");}
MyTask::MyTask(const MyTask&){printf("Copy Construct.\n");};
MyTask::MyTask(const MyTask&& T){}
MyTask::~MyTask(){};

