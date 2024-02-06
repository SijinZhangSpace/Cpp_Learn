#include <iostream>

using std::cout;
using std::endl;

class Singleton {

public:

    static Singleton *getInstance()
    {
        if(nullptr == _pInstance)
        {
            _pInstance = new Singleton();
        }
        return _pInstance;
    }

private:

    //将AutoRelease作为Singleton的内部类
    class AutoRelease {
    public:
        AutoRelease() {}
    
        ~AutoRelease()
        {
            if(_pInstance) //当单例对象已创建时
            {
                delete _pInstance; //回收空间
                _pInstance = nullptr; //指针置空
            }
        }
    };
private:
    Singleton() {}

    ~Singleton() {}

private:
    static Singleton *_pInstance;
    static AutoRelease _ar;
};

Singleton *Singleton::_pInstance = getInstance();
Singleton::AutoRelease Singleton::_ar;

void test()
{
    Singleton::getInstance();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
