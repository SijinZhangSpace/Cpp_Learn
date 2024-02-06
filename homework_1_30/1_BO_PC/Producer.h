#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include "Thread.h"
#include "TaskQueue.h"

class Producer
{
public:
    Producer();
    void produce(TaskQueue &);
};

#endif