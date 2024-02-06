#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "TaskQueue.h"

class Consumer
{
public:
    Consumer();
    void consume(TaskQueue &);
};

#endif