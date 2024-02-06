#include <iostream>
#include <math.h>
#define _USE_MATH_DEFINES
#define pi M_PI

using std::cout;
using std::cin;
using std::endl;

class Circle {
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

class Cylinder
: public Circle {
public:
    Cylinder(double r, double h)
        : Circle(r)
        , _h(h) {}

    double getVolume() {
        double ar = Circle::getArea();
        return ar * _h;
    }

    void showVolume() {
        cout << "The volume is " << getVolume() << endl << endl;
    }
private:
    double _h;
};

void test(){
    Cylinder cyld_1(4, 5);
    cyld_1.showVolume();

    Cylinder cyld_2(6, 8);
    cyld_2.showVolume();
}

int main()
{
    test();
    return 0;
}

