#include <iostream>

using std::cout;
using std::endl;

//单例模式类
class Singleton {

    //声明AutoRelease函数为Singleton的友元函数
    friend class AutoRelease;

public:
    //获取单例对象
    static Singleton *getInstance() {
        //如果对象未创建
        if(nullptr == _pInstance)
        {
            _pInstance = new Singleton(); //申请空间
        }
        return _pInstance;
    }

private:
    
    //构造函数、析构函数私有化
    Singleton() {}
    ~Singleton() {}

private:

    //静态指针
    static Singleton *_pInstance;
};

//静态成员类外初始化
Singleton *Singleton::_pInstance = nullptr;

class AutoRelease {

public:

    AutoRelease() {}
    
    //在AutoRelease析构函数中销毁Singleton对象
    ~AutoRelease() {
        //如果对象已创建
        if(Singleton::_pInstance) {
            delete Singleton::_pInstance; //回收空间
            Singleton::_pInstance = nullptr; //指针置空
        }
        cout << "Destroy Singleton Object" << endl;
    }
};

void test(){
    Singleton *_sig = Singleton::getInstance();
    AutoRelease _ar;
}

int main(){
    test();
    return 0;
}
