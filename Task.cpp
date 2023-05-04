//
// Created by xuejun on 23-4-21.
//
#include <iostream>
#include <memory>
#include "Task.h"


int MyTask::run()
{
    std::cout<<this->name<<"is running "<<std::endl;

    return 100;
}
