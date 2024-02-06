#include "vector.h"
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Computer
{
    friend ostream &operator<<(ostream &, const Computer);
public:
    Computer(const char *brand = " ", int price = 0)
    : _brand(new char[strlen(brand) + 1])
    , _price(price) 
    {
        strcpy(_brand, brand);
    }

    char* getBrand() const
    {
        return _brand;
    }

    int getPrice() const
    {
        return _price;
    }

    void print()
    {
        cout << "Computer: " << _brand << "; Price: " << _price << endl ;
    }


private:
    char *_brand;
    int _price;
};

ostream &operator<<(ostream &stream, const Computer &com)
{
    stream << "Brand: " << com.getBrand() << endl
           << "Price: " << com.getPrice() << endl;
    return stream;
}

void test()
{
    cout << "=== Init new Vector ===" << endl;
    Vector<Computer> vec;
    cout <<"vec.size() = " << vec.size() << endl;
    cout <<"vec.capacity() = " << vec.capacity() << endl << endl;

    cout << "=== Push elemts in Vector ===" << endl;
    vec.push_back(Computer("SanXing",8000));
    vec.push_back(Computer("ThinkPad",12000));
    for(Vector<Computer>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        it->print();
    }
    cout <<"vec.size() = " << vec.size() << endl;
    cout <<"vec.capacity() = " << vec.capacity() << endl;
    vec.push_back(Computer("HuaWei",6000));
    for(Vector<Computer>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        it->print();
    }
    cout <<"vec.size() = " << vec.size() << endl;
    cout <<"vec.capacity() = " << vec.capacity() << endl << endl;

    cout << "=== Pop elements out of Vector ===" << endl;
    vec.pop_back();  
    for(Vector<Computer>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        it->print();
    }
    cout <<"vec.size() = " << vec.size() << endl;
    cout <<"vec.capacity() = " << vec.capacity() << endl;
    vec.pop_back();  
    for(Vector<Computer>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        it->print();
    }
    cout <<"vec.size() = " << vec.size() << endl;
    cout <<"vec.capacity() = " << vec.capacity() << endl;
}

int main()
{
    test();
    return 0;
}

