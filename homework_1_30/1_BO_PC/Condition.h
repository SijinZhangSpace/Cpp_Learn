#ifndef __CONDITION_H__
#define __CONDITION_H__

//a.h(包含了b.h) a.cc   
//b.h(包含a.h) b.cc  
/* #include "MutexLock.h" */
#include <pthread.h>

class MutexLock;//前向声明,建议

class Condition
{
public:
    Condition(MutexLock &mutex);
    ~Condition();

    //等待函数
    void wait();
    //发通知
    void notify();
    void notifyAll();

private:
    MutexLock &_mutex;//互斥锁的引用
    pthread_cond_t _cond;//条件变量

};

#endif
