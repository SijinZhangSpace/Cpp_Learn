#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

using std::function;

class Thread
{
    using ThreadCallback = function<void()>;
public:
    Thread(ThreadCallback &&);
    ~Thread();
    
    void start();
    void stop();

private:
    static void *threadFunc(void *);

private:
    pthread_t _pID;//_thid;//线程id
    bool _isRunning;
    ThreadCallback _cb;
};

#endif

