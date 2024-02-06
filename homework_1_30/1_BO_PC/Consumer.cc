#include <iostream>
#include <unistd.h>
#include "Consumer.h"
using namespace std;

Consumer::Consumer() {}

void Consumer::consume(TaskQueue &taskQue)
{
    size_t cnt = 20;
    while(cnt--)
    {
        int num = taskQue.pop();
        cout << "Consume num: " << num << endl;
        sleep(1);
    }
}