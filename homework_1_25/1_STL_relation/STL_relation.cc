#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print(vector<int> vec)
{
    for(auto it = vec.begin(); it != vec.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void test()
{
    vector<int> vec = {1, 3 ,5 ,7, 9, 11};
    cout << "Initialize vector: ";
    print(vec);

    vector<int>::iterator it = find(vec.begin(), vec.end(), 7);
    cout << "find result: " << *it << endl;

    vec.erase(it);
    cout << "Changed vector: ";
    print(vec);

}

int main()
{
    test();
    return 0;
}
