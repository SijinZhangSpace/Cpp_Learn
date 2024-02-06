#include <iostream>
#include <math.h>
#define _USE_MATH_DEFINES
#define pi M_PI

using std::cout;
using std::cin;
using std::endl;

class Circle{
public:
    Circle()
        : _r(0) {}

    Circle(double r)
        : _r(r) {}

    double getArea() {
        return pi * _r * _r;
    }

    double getPerimeter() {
        return 2 * _r * pi;
    }

    void show() {
        cout << "The area is " << getArea() << endl
             << "The perimeter is " << getPerimeter() << endl << endl;
    }
private:
    double _r;
};

void test(){
    Circle cr_0;
    cr_0.show();

    Circle cr_3(3);
    cr_3.show();
}

int main()
{
    test();
    return 0;
}

