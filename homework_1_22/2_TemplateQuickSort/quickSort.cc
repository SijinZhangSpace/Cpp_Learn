#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T, typename Compare = less<T>> 
class MyQsort 
{ 
public:     
    MyQsort(T *arr, size_t size, Compare com);     
    void quick(int left, int right, Compare &com);     
    int partition(int left, int right, Compare &com);     
    void print(); 
private:    
    vector<T> _vec; 
};

template<typename T , typename Compare>
MyQsort<T, Compare>::MyQsort(T *arr, size_t size, Compare com)
{
    for (size_t i = 0; i < size; ++i)
        _vec.push_back(arr[i]);
    quick(0, _vec.size() - 1, com);
}

template<typename T , typename Compare>
void MyQsort<T, Compare>::quick(int left, int right, Compare &com)
{
     if(left<right)
    {
        int pivot = partition(left, right, com);
        quick(left,pivot - 1, com);
        quick( pivot + 1, right, com);
    }
}

template<typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right, Compare &com)
{
    int indexi,indexk;
    for(indexi=left, indexk = left; indexi<right;indexi++)
    {
        if(com(_vec[indexi],_vec[right]))//以数组最右边的元素作为pivot
        {
            swap(_vec[indexi],_vec[indexk]);
            ++indexk;//indexk记录的是小于pivot的元素个数，
        }
    }
    swap(_vec[indexk], _vec[right]);//交换后indexk左边是小于pivot的元素，右边是大于Pivot的元素
    return indexk;
}

template<typename T, typename Compare>
void MyQsort<T, Compare>::print()
{
    cout << "The Result: ";
    for (auto it = _vec.begin(); it != _vec.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void test()
{
    size_t size;
    cout << "Please enter size of sequence to sort: ";
    cin >> size;
    int arr[size];
    int *pInt = arr;
    cout << "Please enter the sequence: ";
    for(size_t i = 0; i < size; ++i)
        cin >> pInt[i];
    cout << "Current Sequence: ";
    for(size_t i = 0; i < size; ++i)
        cout << pInt[i] << " ";
    cout << endl;
    MyQsort<int> my_sort(pInt, size, less<int>());
    my_sort.print();
}

int main()
{
    test();
    return 0;
}