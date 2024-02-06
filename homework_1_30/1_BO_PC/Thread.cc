#include <stdio.h>
#include <iostream>
#include <cstring>
#include <functional>
#include "Thread.h"

using namespace std;

#define ERROR_CHECK(ret, funcName) \
do{ \
    if(ret != 0) \
    { \
        printf("%s : %s \n", funcName, strerror(ret));\
        exit(1); \
    } \
}while(0);

using std::cout;
using std::endl;

Thread::Thread(ThreadCallback &&cb)
: _pID(0)
, _isRunning(false)
, _cb(std::move(cb)) {}

Thread::~Thread() {}

void Thread::start()
{
    int ret = pthread_create(&_pID, nullptr, threadFunc, this);
    ERROR_CHECK(ret, "pthread_create");

    _isRunning = true;
}

void Thread::stop()
{
    if(_isRunning)
    {
        int ret = pthread_join(_pID, nullptr);
        ERROR_CHECK(ret, "pthread_join")

        _isRunning = false;
    }
}

void *Thread::threadFunc(void *arg)
{
    Thread *pth = static_cast<Thread *>(arg);
    if(pth) pth->_cb();
    else cout << "Thraed Error" << endl;

    pthread_exit(nullptr);
}

