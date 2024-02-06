#include <iostream>

using std::cout;
using std::cin;
using std::endl;

template<typename T = int, size_t size = 10>
class Queue{
public:
    Queue();
    ~Queue();
    bool empty() const;
    bool full() const;
    void push(const T &value);
    void pop();
    T front();
    T back();
private:
    int _front;//队首
    int _rear;//队尾
    int _size;//容量
    int *_data;//存放元素
};

template <typename T, size_t size>
Queue<T, size>::Queue()
: _front(0)
, _rear(0)
, _size(size + 1)
, _data(new int[size + 1]()) 
{
    cout << "Queue()" << endl;
}

template <typename T, size_t size>
Queue<T, size>::~Queue()
{
    if (_data)
    {
        delete [] _data;
        _data = nullptr;
    }
    cout << "~Queue()" << endl;
}

template <typename T, size_t size>
bool Queue<T, size>::empty() const
{
    return _front == _rear;
}

template <typename T, size_t size>
bool Queue<T, size>::full() const
{
    return _front == (_rear + 1) % _size;
}

template <typename T, size_t size>
void Queue<T, size>::push(const T &value)
{
    if (!full())
    {
        _data[_rear++] = value;
        _rear %= _size;
    }
    else
    {
        cout << "The Queue is already full!" << endl;
        return;
    }
}

template <typename T, size_t size>
void Queue<T, size>::pop()
{
    if(!empty())
    {
        ++_front;
        _front %= _size;
    }
    else
    {
        cout << "The Queue is already empty!" << endl;
        return;
    }
}

template <typename T, size_t size>
T Queue<T, size>::front()
{
    return _data[_front];
}

template <typename T, size_t size>
T Queue<T, size>::back()
{
    return _data[(_rear - 1 + _size) % _size];
}

void test()
{
    Queue<int, 10> que;
    cout << "Queue::empty() = " << que.empty() << endl;
    cout << "Queue::full() = " << que.full() << endl;
    cout << "Front of Queue is " << que.front() << endl;
    cout << "Back of Queue is " << que.back() << endl << endl;

    que.push(1);
    cout << "Queue::empty() = " << que.empty() << endl;
    cout << "Queue::full() = " << que.full() << endl;
    cout << "Front of Queue is " << que.front() << endl;
    cout << "Back of Queue is " << que.back() << endl << endl;

    for(int idx = 2; idx != 11; ++idx)
    {
        que.push(idx);
    }
    cout << "Queue::empty() = " << que.empty() << endl;
    cout << "Queue::full() = " << que.full() << endl;
    cout << "Front of Queue is " << que.front() << endl;
    cout << "Back of Queue is " << que.back() << endl << endl;

    cout << "Elements in Queue are : ";
    while(!que.empty())
    {
        cout << que.front() << " ";
        que.pop();
    }
    cout << endl << endl;
}

int main()
{
    test();
    return 0;
}

