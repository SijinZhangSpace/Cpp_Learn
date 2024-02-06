#include <iostream>
#include "RssReader.h"

using std::cout;
using std::cin;
using std::endl;

void test(){
    RssReader it;
    it.parseRss();//解析
    it.dump("pagelib.txt");
}

int main()
{
    test();
    return 0;
}

