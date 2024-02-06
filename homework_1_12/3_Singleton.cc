#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

class Singleton {

public:

    static Singleton *getInstance() {
        if(nullptr == _pInstance)
        {
            _pInstance = new Singleton();
            atexit(destroy);
        }
        return _pInstance;
    }

    //静态destroy以访问静态成员
    static void destroy() {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

private:
    Singleton() {}
    ~Singleton() {}

private:
    static Singleton *_pInstance;
};

//饿汉模式初始化对象
Singleton *Singleton::_pInstance = Singleton::getInstance();

void test()
{
    Singleton::getInstance();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
