#include <iostream>
#include <memory>
#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"

using namespace std;

void test()
{
    TaskQueue taskQue(10);
    Producer pro;
    Consumer con;
    Thread produceTh(bind(&Producer::produce, &pro, ref(taskQue)));
    Thread consumeTh(bind(&Consumer::consume, &con, ref(taskQue)));

    produceTh.start();
    consumeTh.start();

    produceTh.stop();
    consumeTh.stop();
}

int main()
{
    test();
    return 0;
}