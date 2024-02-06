#include <iostream>
#include <vector>

using namespace std;

template<typename T, typename Compare>
class MyQuickSort
{
public:
    MyQuickSort(T *arr, size_t size, Compare );
    void quick(int left, int right, Compare &);
    int partition(int left, int right, Compare &);
    void print();
private:
    vector<T> _vec;
};

template<typename T,typename Compare>
MyQuickSort<T,Compare>::MyQuickSort(T * arr, size_t size, Compare com)
{
    for(size_t i = 0; i < size; i++)
    {
        _vec.push_back(arr[i]);
    }

    quick(0, _vec.size() - 1, com);
}

template<typename T,typename Compare>
void MyQuickSort<T, Compare>::quick(int left, int right, Compare &com)
{
    int pivot;
    if(left < right)
    {
        pivot = partition(left, right, com);
        quick(left, pivot - 1, com);//左边递归调用
        quick(pivot + 1, right, com);//右边递归调用
    }
}

template<typename T, typename Compare>
int MyQuickSort<T, Compare>::partition(int left, int right, Compare &com)
{
    int indexi, indexk;
    for(indexi = left, indexk = left; indexi < right; ++indexi)
    {
        if(com(_vec[indexi], _vec[right]))
        {
            swap(_vec[indexi], _vec[indexk]);
            ++indexk;
        }

    }
    swap(_vec[indexk], _vec[right]);

    return indexk;
}

template <typename T, typename Compare>
void MyQuickSort<T, Compare>::print()
{
    for(auto &elem : _vec)
    {
        cout << elem << "  ";
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

    MyQuickSort<int, less<int>> mySort(arr, size, less<int>());
    mySort.print();
}

int main()
{
    test();
    return 0;
}

