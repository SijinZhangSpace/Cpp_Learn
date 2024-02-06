#include <iostream>

using std::cout;
using std::endl;

int findHalfShow(int nums[], int nums_len)
{
    if(nums_len <= 0)
    {
        return -2;
    }
    int temp = nums_len/2;
    int count = 0;
    for(int i=0; i < nums_len; i++)
    {
        for(int j=i; j< nums_len; j++)
        {
            if(nums[i] == nums[j])
            {
                count++;
            }
        }
        if(count > temp)
        {
            return nums[i];
        }
        else
        {
            count = 0;
        }
    }
    return -1;
}

int main()
{
    int nums[] = {1, 2, 4, 4, 5, 5, 5, 5, 5};
    int x = findHalfShow(nums, 9);
    if(x == -2)
    {
        cout << "nums[] Error" << endl;
    }
    else if(x == -1)
    {
        cout << "No suitable number" << endl;
    }
    else
    {
        cout << "The number is " << x << endl;
    }
    return 0;
}

