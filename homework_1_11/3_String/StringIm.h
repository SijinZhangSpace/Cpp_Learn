#ifndef __STRINGIM_H__
#define __STRINGIM_H__

#include <iostream>
#include <string>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

class String {
public:
	String();
	String(const char*);
	String(const String&);
	~String();

	String& operator=(const String&);
	String& operator=(const char*);

	String& operator+=(const String&);
	String& operator+=(const char*);

    char& operator[](std::size_t index){
        if (index < size()){
            return _pstr[index];
        }
        else{
            static char nullchar = '\0';
            return nullchar;
        }
    }

    const char& operator[](std::size_t index) const{
        if (index < size()){
            return _pstr[index];
        }
        else{
            static char nullchar = '\0';
            return nullchar;
        }
    }

	std::size_t size() const {
		return strlen(_pstr);
	}

    const char* c_str() const {
        return _pstr;
    }

	friend bool operator==(const String& str1, const String& str2);
	friend bool operator!=(const String& str1, const String& str2);

	friend bool operator<(const String& str1, const String& str2);
	friend bool operator>(const String& str1, const String& str2);
	friend bool operator<=(const String& str1, const String& str2);
	friend bool operator>=(const String& str1, const String& str2);

	friend std::ostream& operator<<(std::ostream&, const String& str);
	friend std::istream& operator>>(std::istream&, String& str);
    
private:
	char* _pstr;
};

#endif
