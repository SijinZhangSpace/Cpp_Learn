#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <iostream>
#include <string.h>

using namespace std;

template<typename T> 
class Vector 
{ 
public:     
    Vector();     
    ~Vector();          
    void push_back(const T &);      
    void pop_back();         
    int size();     
    int capacity();

    class iterator
	{
	public:
		iterator(T*ptr = NULL) 
        : _ptr(ptr){}

		bool operator!=(const iterator&it)
		{
			return _ptr != it._ptr;
		}

		bool operator++()
		{
			_ptr++;
			return true;
		}

        T* operator->() const
        { 
            return _ptr;
        }

		T&operator*()
		{
			return *_ptr;
		}

		T operator[](int index)
		{
			return _ptr[index];
		}

	private:
		T*_ptr;
	};

    iterator begin()
    {
        return iterator(_start);
    }

    iterator end()
    { 
        return iterator(_finish); 
    }

private:     
    void reallocate();//重新分配内存,动态扩容要用的 
private:         
    static allocator<T> _alloc;          
    T *_start;                 //指向数组中的第一个元素     
    T *_finish;                //指向最后一个实际元素之后的那个元素     
    T *_end_of_storage;        //指向数组本身之后的位置 
};

template<typename T> 
allocator<T> Vector<T>::_alloc;

template<typename T>
Vector<T>::Vector()
{
    _start = _alloc.allocate(0);
    _finish = _start;
    _end_of_storage = _start;
}

template<typename T>
Vector<T>::~Vector()
{
    _alloc.destroy(_start);
    _alloc.deallocate(_start, capacity());
    _start = nullptr;
    _finish = nullptr;
    _end_of_storage = nullptr;
}

template<typename T>
void Vector<T>::reallocate()
{
    size_t newCapacity = (size() == 0) ? 1 : size() * 2;
    T* temp = _alloc.allocate(newCapacity);
    memcpy(temp, _start, size() * sizeof(T));
    for(auto it = _start; it != _finish; it++)
    {
        _alloc.destroy(it);
    }
    _alloc.deallocate(_start, capacity());

    _start = temp;
    _finish = _start + newCapacity/2;
    _end_of_storage = _start + newCapacity;

    temp = nullptr;
}

template<typename T>
int Vector<T>::size()
{
    return _finish - _start;
}

template<typename T>
int Vector<T>::capacity()
{
    return _end_of_storage - _start;
}

template<typename T>
void Vector<T>::push_back(const T &t)
{
    cout << "Push new element in Vector." << endl;
    if(size() == capacity())
    {
        reallocate();
    }
    _alloc.construct(_finish++, t);
}

template<typename T>
void Vector<T>::pop_back()
{
    cout << "Pop the last element out of Vector." << endl;
    if(0 == size())
    {
        cerr << "The Vector is empty." << endl;
        return;
    }
    _alloc.destroy(--_finish);
}

#endif //__VECTOR_H__
