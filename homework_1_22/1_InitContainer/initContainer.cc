#include <iostream>
#include <vector>
#include <list>
#include <deque>

using namespace std;

template <typename T>
void printContainer(T cnter)
{
	for (auto it = cnter.begin(); it != cnter.end(); ++it)
		cout << *it << " ";
}

int main()
{
	//无参初始化
	vector<int> vec1;
	list<int> lst1;
	deque<int> dq1;
	cout << "Vector Print: ";
	printContainer(vec1);
	cout << "List Print: ";
	printContainer(lst1);
	cout << "Deque Print: ";
	printContainer(dq1);
	cout << endl << endl;

	//通过count个value初始化
	int count = 6, value = 8;
	vector<int> vec2(count, value);
	list<int> lst2(count, value);
	deque<int> dq2(count, value);
	cout << "Vector Print: ";
	printContainer(vec2);
	cout << "\nList Print: ";
	printContainer(lst2);
	cout << "\nDeque Print: ";
	printContainer(dq2);
	cout << endl << endl;

	//通过迭代器使用指定范围内元素初始化
	int arr[5] = { 2, 4, 6, 8, 10 };
	vector<int> vec3(arr, arr + 5);
	list<int> lst3(arr, arr + 5);
	deque<int> dq3(arr, arr + 5);
	cout << "Vector Print: ";
	printContainer(vec3);
	cout << "\nList Print: ";
	printContainer(lst3);
	cout << "\nDeque Print: ";
	printContainer(dq3);
	cout << endl << endl;

	return 0;
}