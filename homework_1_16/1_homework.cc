#include <iostream>

using std::endl;
using std::cout;

class Base
{
public:
	Base(int i)
	{
		b = i;
	}
	
	//(1)
	
	Base() :b(0) {}
	
	virtual void Print()
	{
		cout << "Base 's Print() called." << endl;
	}
protected:
	int b;
};

class Derive1
	:public Base
{
public:
	Derive1()
		: Base() {}
	
	void Print()
	{
		cout << "Derive1's Print() called." << endl;
	}
};

class Derive2
	:public Base
{
public:
	Derive2()
		: Base() {}

	void Print()
	{
		cout << "Derive2's Print() called. " << endl;
	}
};

//Base  * obj
void fun(Base* obj)
{
	obj->Print();
}

int main(void)
{
	Derive1 d1;
	Derive2 d2;
	Base* b1 = &d1;
	Base* b2 = &d2;
	fun(b1);
	fun(b2);
	return 0;
}
