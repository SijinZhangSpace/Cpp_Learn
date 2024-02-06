#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Producer.h"

using namespace std;

Producer::Producer() {}

void Producer::produce(TaskQueue &taskQue)
{
    srand(clock());
    size_t cnt = 20;
    while(cnt--)
    {
        int num = rand() % 100;
        taskQue.push(num);
        cout << "Prodeuce num: " << num << endl;
        sleep(1);
    }
}
