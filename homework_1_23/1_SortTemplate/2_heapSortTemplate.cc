#include <iostream>
#include <vector>

using namespace std;

template<typename T, typename Compare>
class MyHeapSort
{
public:
    MyHeapSort(T *arr, size_t size,Compare);
    void heapAdjust(size_t ,size_t ,Compare&);
    void sort(Compare&);
    void print();

private:
    vector<T> vec;
};

template <typename T, typename Compare >
MyHeapSort<T, Compare>::MyHeapSort(T *arr, size_t size, Compare com)
{
    for (size_t i = 0; i < size; i++)
    {
        vec.push_back(arr[i]);
    }
    for (int i = size/2 - 1; i >= 0; i--)
    {
        heapAdjust(i, size,com);
    }
    swap(arr[0], arr[size - 1]);
    sort(com);
}

template <typename T, typename Compare >
void MyHeapSort<T, Compare>::heapAdjust(size_t adjustpos, size_t arrlen, Compare& com)
{

    size_t dad = adjustpos;
    size_t son= 2 * dad + 1;
    while(son < arrlen)
    {
        if(son + 1 < arrlen && com(vec[son],vec[son + 1]))
        {
            ++son;
        }
        if(com(vec[dad], vec[son]))
        {
            swap(vec[dad], vec[son]);
            dad = son;
            son= 2 * dad + 1;
        }
        else
        {
            break;
        }
    }
}

template <typename T, typename Compare >
void MyHeapSort<T, Compare>::sort(Compare& com)
{
    size_t size = vec.size();
    for (size_t i = size; i > 1; i--)
    {
        heapAdjust(0, i, com);
        swap(vec[0], vec[i - 1]);
    }
}

template <typename T, typename Compare>
void MyHeapSort<T,Compare>::print()
{
    for(auto &elem : vec)
    {
        cout<< elem << "  ";
    }
    cout << endl;
}

void test()
{
    int size;
    cout << "Enter size of arry: ";
    cin >> size;
    int arr[size];
    cout << "Enter arry elements: ";
    for(int i = 0; i < size; ++i)
    {
        cin >> arr[i];
    }

    MyHeapSort<int, less<int>> mySort(arr, size, less<int>());
    mySort.print();
}

int main()
{
    test();
    return 0;
}

