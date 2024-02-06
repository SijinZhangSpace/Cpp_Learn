#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include <pthread.h>

class MutexLock
{
public:
    MutexLock();
    ~MutexLock();

    //上锁
    void lock();
    //尝试上锁
    void tryLock();
    //解锁
    void unlock();
    //获取数据成员
    pthread_mutex_t *getMutexLockPtr();

private:
    pthread_mutex_t _mutex;//互斥锁的变量
};

#endif
