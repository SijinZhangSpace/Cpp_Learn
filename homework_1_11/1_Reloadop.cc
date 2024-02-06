#include <iostream>

using std::cin;
using std::cout;
using std::endl;

/* C++中成员指针访问运算符使用实例 */

class EgA {
public:
	EgA(int value = 0)
		: _value(value)
	{}

	int getValue() const {
		return _value;
	}

private:
	int _value;
};

class EgB {
public:
	EgB(EgA *pA)
		: _pEgA(pA)
	{}

    //重载运算符->
	EgA *operator->()
	{
		return _pEgA;
	}

    //重载解引用运算符
    EgA &operator*(){
        return *_pEgA;
    }

	~EgB() {
		if (_pEgA) {
			delete _pEgA;
			_pEgA = nullptr;
		}
	}

private:
	EgA* _pEgA;
};

void test() {
	EgA *pA = new EgA(5);
	EgB pB(pA);

	//类EgB的对象pB调用类EgA的函数getValue
	cout << "value of Object pA in Class EgA is " << pB->getValue() << endl;
	cout << "value of Object pA in Class EgA is " << (*pB).getValue() << endl;
}

int main() {
	test();
	return 0;
}
