#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

//在写时复制中，怎么去实现呢？
//思想就是：浅拷贝 + 引用计数
class String
{
public:
    String()
        : _pstr(new char[5]() + 4)
    {
        cout << "String()" << endl;
        initRefCount();
    }

    String(const char* pstr)
        : _pstr(new char[strlen(pstr) + 5]() + 4)
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
        initRefCount();
    }

    //String s2 = s1;
    String(const String& rhs)
        : _pstr(rhs._pstr)//浅拷贝
    {
        cout << "String(const String &)" << endl;
        increaseRefCount();
    }

    //s3 = s2
    String& operator=(const String& rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        if (this != &rhs)//1、自复制
        {
            //shift + *  n
            release();//释放左操作数

            _pstr = rhs._pstr;//3、浅拷贝
            increaseRefCount();
        }
        return *this;//4、返回*this
    }

    /*char& operator[](size_t idx)
    {
        if (idx < size())
        {
            //是不是共享
            if (getRefCount() > 1)
            {
                char* ptmp = new char[size() + 5]() + 4;
                strcpy(ptmp, _pstr);
                decreaseRefCount();

                _pstr = ptmp;
                initRefCount();
            }
            return _pstr[idx];
        }
        else
        {
            static char nullchar = '\0';
            return nullchar;
        }
    }*/

    ~String()
    {
        cout << "~String()" << endl;
        release();
    }

private:
    //代理商
    class Proxy {
    public:
        Proxy(String &str, size_t idx)
            : _str(str)
            , _idx(idx) {}

        char& operator=(const char& str) {
            if (_idx < _str.size()) {
                if (_str.getRefCount() > 1) {
                    char* ptmp = new char[_str.size() + 5]() + 4;
                    strcpy(ptmp, _str._pstr);
                    _str.decreaseRefCount();

                    _str._pstr = ptmp;
                    _str.initRefCount();
                }
                _str._pstr[_idx] = str;
                return _str._pstr[_idx];
            }
            else {
                static char nullchar = '\0';
                return nullchar;
            }
        }

        //将自定义的CharProxy转换为char
        operator char()
        {
            return _str._pstr[_idx];
        }

    private:
        String& _str;
        size_t _idx;
    };

    void release()
    {
        decreaseRefCount();
        if (0 == getRefCount())//2、释放左操作数
        {
            delete[](_pstr - 4);
        }
    }

    void initRefCount()
    {
        *(int*)(_pstr - 4) = 1;
    }

    void increaseRefCount()
    {
        ++* (int*)(_pstr - 4);
    }

    void decreaseRefCount()
    {
        --* (int*)(_pstr - 4);
    }

    size_t size() const
    {
        return strlen(_pstr);
    }

public:
    Proxy operator[](size_t idx)
    {
        return Proxy(*this, idx);
    }

    const char* c_str() const
    {
        return _pstr;
    }

    int getRefCount() const
    {
        return *(int*)(_pstr - 4);
    }

    friend std::ostream& operator<<(std::ostream& os, const String& rhs);
private:
    char* _pstr;
};

std::ostream& operator<<(std::ostream& os, const String& rhs)
{
    if (rhs._pstr)
    {
        os << rhs._pstr;
    }

    return os;
}

void test()
{
    //如果要直接打印引用计数?
    String s1("hello");
    String s2 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    printf("&s1 = %p\n", s1.c_str());
    printf("&s2 = %p\n", s2.c_str());
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;

    cout << endl;
    String s3("world");
    cout << "s3 = " << s3 << endl;
    printf("&s3 = %p\n", s3.c_str());
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;

    cout << endl;
    s3 = s1;
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("&s1 = %p\n", s1.c_str());
    printf("&s2 = %p\n", s2.c_str());
    printf("&s3 = %p\n", s3.c_str());
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;

    cout << endl << "对s3[0]执行写操作" << endl;
    s3[0] = 'H';//char = char
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("&s1 = %p\n", s1.c_str());
    printf("&s2 = %p\n", s2.c_str());
    printf("&s3 = %p\n", s3.c_str());
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;

    //代码的问题在哪里？
    //不能区分读与写操作
    cout << endl << "对s1[0]执行读操作" << endl;
    cout << "s1[0] = " << s1[0] << endl;//cout << char
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    printf("&s1 = %p\n", s1.c_str());
    printf("&s2 = %p\n", s2.c_str());
    printf("&s3 = %p\n", s3.c_str());
    cout << "s1.getRefCount() = " << s1.getRefCount() << endl;
    cout << "s2.getRefCount() = " << s2.getRefCount() << endl;
    cout << "s3.getRefCount() = " << s3.getRefCount() << endl;
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}


