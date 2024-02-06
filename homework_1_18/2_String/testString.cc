#include "StringIm.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void judgeEqual(String &str1, String &str2){
    if (str1 == str2) {
        cout << "Two String is Same" << endl;
    }
    else {
        cout << "Two String is different" << endl;
    }
}

void judgeLess(String &str1, String &str2){
    if (str1 < str2) {
        cout << "Two String is Same" << endl;
    }
    else {
        cout << "Two String is different" << endl;
    }
}

void judgeLessOrEqual(String &str1, String &str2){
    if (str1 == str2) {
        cout << "Two String is Same" << endl;
    }
    else {
        cout << "Two String is different" << endl;
    }
}

void test() {
    cout << endl << endl;
	String _str1("Test");
	String _str2(_str1);
    String _str3("DifferentOne");

    cout << "====== Init String Objects======" << endl;
	cout << "_str1 = " << _str1 << endl;
	cout << "_str2 = " << _str2 << endl;
	cout << "_str3 = " << _str3 << endl;
    cout << "_str1[1] = " << _str1[1] << endl;
    cout << endl << endl;

    cout << "====== Test Operator ======" << endl; 
    cout << "Result of _str1 == _str2 is ";
    judgeEqual(_str1, _str2);
    cout << "Result of _str2 == _str3 is ";
    judgeEqual(_str2, _str3);
    cout << "Result of _str1 > _str2 is ";
    judgeLess(_str1, _str2);
    cout << "Result of _str2 > _str3 is ";
    judgeLess(_str2, _str3);
    cout << "Result of _str1 <= _str2 is ";
    judgeLessOrEqual(_str1, _str2);
    cout << "Result of _str2 <= _str3 is ";
    judgeLessOrEqual(_str2, _str3);
    cout << endl << endl;
}

void test1() {
    String str = "Hello";
    str = String("World");
}

int main() {
	test1();
	return 0;
}
