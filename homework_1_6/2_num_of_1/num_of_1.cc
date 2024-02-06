#include <iostream>

#define MAX 500

using std::cout;
using std::cin;
using std::endl;

int toBinary(int n, int bin[])
{
    int i=0;
    int len = 0;
    for(int i=0; n>0; i++)
    {
        bin[i] = n%2;
        n = n/2;
        len++;
    }
    int low = 0;
    int high = len-1;
    int temp;
    while(low < high)
    {
        temp = bin[low];
        bin[low] = bin[high];
        bin[high] = temp;
        low++;
        high--;
    }
    return len;
}

int oneCalc(int num)
{
    int bin[MAX];
    int size = toBinary(num, bin);
    int count = 0;
    for(int i=0; i < size; i++)
    {
        if(bin[i] == 1)
            count++;
    }
    return count;
}

int main()
{
    int x;
    cin >> x;
    cout << "Amount of 1 in binary "<< x << " is " << oneCalc(x) << endl;
    return 0;
}

