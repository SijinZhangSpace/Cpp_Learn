#include "StringIm.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

String::String()
	:_pstr(nullptr) {
	cout << "String():_pstr(nullptr)" << endl;
}

String::String(const char* str)
	:_pstr(new char[strlen(str) + 1]()) {
	strcpy(_pstr, str);
	cout << "String(const char*)" << endl;
}

String::String(const String& str)
	:_pstr(nullptr) {
	cout << "String(const String&)" << endl;
	_pstr = new char[str.size()]();
	strcpy(_pstr, str._pstr);
}

String::String(String &&rhs)
    : _pstr(rhs._pstr)
{
    cout << "String(String &&)" <<endl;
    rhs._pstr = nullptr;
}

String::~String() {
	if (_pstr) {
		delete [] _pstr;
		_pstr = nullptr;
	}
	cout << "~String()" << endl;
}

String& String::operator=(const String& str) {
	if (_pstr) { //原本_pstr有值
		delete [] _pstr;
		_pstr = nullptr; //清空原本值
	}
	//将新值传入
	_pstr = new char[str.size() + 1]();
	strcpy(_pstr, str._pstr);
	cout << "String& operator=(const String&)" << endl;
	return *this;
}

String& String::operator=(String &&rhs)
{
    cout << "String &operator=(String &&)" << endl;
    if(this != &rhs)
    {
        delete [] _pstr;
        _pstr = nullptr;

        _pstr = rhs._pstr;
        rhs._pstr = nullptr;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
	os << s._pstr;
	return os;
}

std::istream& operator>>(std::istream& is, String& s) {
	is >> s._pstr;
	return is;
}

bool operator==(const String& lstr, const String& rstr) {
    if (strcmp(lstr._pstr, rstr._pstr) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

bool operator!=(const String& lstr, const String& rstr) {
    if (strcmp(lstr._pstr, rstr._pstr) == 0) {
        return 0;
    }
    else {
        return 1;
    }
}

bool operator<(const String & str1, const String & str2) {
    if (str1.size() < str2.size()) {
        return 1;
    }
    else {
        return 0;
    }
}

bool operator>(const String & str1, const String & str2) {
    if (str1.size() > str2.size()) {
        return 1;
    }
    else {
        return 0;
    }
}

bool operator<=(const String & str1, const String & str2) {
    if (str1.size() <= str2.size()) {
        return 1;
    }
    else {
        return 0;
    }
}

bool operator>=(const String & str1, const String & str2) {
    if (str1.size() >= str2.size()) {
        return 1;
    }
    else {
        return 0;
    }
}
