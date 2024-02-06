#include <iostream>
#include <vector>
#include <string.h>
#include <assert.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

template <typename T>
class Singleton
{
public:
    template<typename ...Args>
    static T* getInstance(Args ...args)
    {
        if (!_pInstance)
        {
            _pInstance = new T(args...);
            _ar;
        }
        return _pInstance;
    }

private:
    Singleton()
    {
        cout <<"Singleton()" << endl;
    }

    ~Singleton()
    {
        cout <<"~Singleton()" << endl;
    }

    class AutoRelease
    {
    public:
        AutoRelease()
        {
            cout << "AutoRelease()" << endl;
        }
    
        ~AutoRelease()
        {
            cout << "~AutoRelease()" << endl;
            if(_pInstance)
            {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

    static T* _pInstance;
    static AutoRelease _ar;
};

template <typename T>
T* Singleton<T>::_pInstance = nullptr;
template <typename T>
typename Singleton<T>::AutoRelease Singleton<T>::_ar;

class Point
{
    friend class Singleton<Point>;
public:
    bool operator==(Point* pt)
    {
        return (_x == pt->_x && _y == pt->_y);
    }

private:
    Point(int ix, int iy)
    : _x(ix)
    , _y(iy)
    {
        cout << "Point()" << endl;
    }

    ~Point()
    {
       cout << "~Point()" << endl;
    }

    int _x;
    int _y;
};

class Computer
{
    friend class Singleton<Computer>;
public:
    bool operator==(Computer* pc)
    {
        return (_name == pc->_name && _price == pc->_price);
    }

private:
    Computer(const char* name = nullptr, int price = 0)
    : _name (new char[strlen(name) + 1]())
    , _price(price)
    {
        strcpy(_name, name);
        cout << "Computer()" << endl;
    }

    ~Computer()
    {
        if(_name!=nullptr)
        {
            delete [] _name;
            _name = nullptr;
        }
        cout << "~Computer()" << endl;
    }

    char* _name;
    int _price;
};

void test()
{
    Computer *pc1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    Computer *pc2 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    assert(pc1 == pc2);
    
    Point *pt3 = Singleton<Point>::getInstance(1, 2);
    Point *pt4 = Singleton<Point>::getInstance(1, 2);
    assert(pt3 == pt4);
}

int main()
{
    test();
    return 0;
}

