#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>

using std::queue;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    //任务队列空与满
    bool empty() const;
    bool full() const;

    //向任务队列中存数据
    void push(const int &value);
    //从任务队列中取数据
    int pop();

private:
    size_t _queSize;//任务队列的大小
    queue<int> _que;//存放数据的数据结构
    MutexLock _mutex;//互斥锁
    Condition _notEmpty;//非空条件变量
    Condition _notFull;//非满条件变量

};

#endif
