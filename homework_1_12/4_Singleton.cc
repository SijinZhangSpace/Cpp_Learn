#include <stdlib.h>
#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

class Singleton {

public:

    static Singleton *getInstance() {
        pthread_once(&_once, init);
        return _pInstance;
    }

    static void init() {
        _pInstance = new Singleton();
        atexit(destroy);
    }

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
    static pthread_once_t _once;
};

Singleton *Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

void test() {
    Singleton::getInstance();
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}
