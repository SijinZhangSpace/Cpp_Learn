#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Person {
public:
    Person(const string &name, int age)
        : _name(name)
        , _age(age) {}

    virtual void display() {
        cout << "Name: " << _name << endl
             << "Age: " << _age << endl;
    }

    string getName() {
        return _name;
    }

    int getAge() {
        return _age;
    }
private:
    string _name;
    int _age;
};

class Employee
: public Person {
public:
    Employee(const string &name, int age,
             const string &department, int salary)
        : Person(name, age)
        , _department(department)
        , _salary(salary) {}

    int getSalary() {
        return _salary;
    }

    virtual void display() {
        cout << "Information of Employee:" << endl
             << "Name : " << getName() << endl
             << "Age : " << getAge() << endl
             << "Salary : " << _salary << endl << endl;
    }
private:
    string _department;
    int _salary;
};

void test() {
    Employee ep_1("ZhangSan", 20, "Dp_1", 5000);
    Employee ep_2("LiSi", 30, "Dp_2", 8000);
    Employee ep_3("WangMaZi", 60, "Dp_3", 3000);

    ep_1.display();
    ep_2.display();
    ep_3.display();

    int sl_1 = ep_1.getSalary();
    int sl_2 = ep_2.getSalary();
    int sl_3 = ep_3.getSalary();

    cout << "The average salary is " << (sl_1 + sl_2 + sl_3)/3 << endl;
}

int main()
{
    test();
    return 0;
}

