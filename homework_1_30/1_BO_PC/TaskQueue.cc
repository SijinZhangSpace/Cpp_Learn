#include "TaskQueue.h"
    
TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex)
{

}

TaskQueue::~TaskQueue()
{

}

//任务队列空与满
bool TaskQueue::empty() const
{
    return _que.size() == 0;
}

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

//向任务队列中存数据
void TaskQueue::push(const int &value)
{
    //1、加锁
    _mutex.lock();
    //2、判断是不是满的
    if(full())
    {
        //2.1、如果是满的，需要做什么？wait
        _notFull.wait();
    }
    //2.2、如果不满，又需要做什么呢？
    //将数据放在任务队列中，也就是_que中
    _que.push(value);
    _notEmpty.notify();//还需要唤醒消费者线程
    //3、解锁
    _mutex.unlock();
}
//从任务队列中取数据
int TaskQueue::pop()
{
    //1、加锁
    _mutex.lock();
    //2、判断是不是空的
    if(empty())
    {
        //2.1、如果是空的，需要做什么？wait
        _notEmpty.wait();
    }
    //2.2、如果不空，又需要做什么呢？
    //将数据放从任务队列取中，也就是_que中
    int tmp = _que.front();
    _que.pop();
    //还需要唤醒生产者线程
    _notFull.notify();
    //3、解锁
    _mutex.unlock();

    return tmp;
}
