//
// Created by xuejun on 23-4-21.
//

#ifndef FEATURES_TASK_H
#define FEATURES_TASK_H

class Task
{
public:
    virtual int run()=0;
    std::string name;

protected:

};


class MyTask:public Task
{
public:
    int run();

private:

};

#endif //FEATURES_TASK_H
