#include <iostream>

using std::cout;
using std::cin;
using std::endl;

/* 编写Base类使下列代码输出为1 */
/* int i=2; */
/* int j=7; */
/* Base x(i); */
/* Base y(j); */
/* cout << (x+y == j - i) << endl; */
/* 提示：本题考查的其实就是运算符重载的知识点。 */

class Base{
public:
    Base(int x = 0)
        : _value(x)
    {}

    Base operator+(const Base &bs){
        Base _bs(_value + bs._value);
        return _bs;
    }

    bool operator==(const int rst){
        return !(_value == rst);
    }

private:
    int _value;
};

void test(){
    int i=2;
    int j=7;

    Base x(i);
    Base y(j);
    cout << (x+y == j - i) << endl;
}

int main()
{
    test();
    return 0;
}

