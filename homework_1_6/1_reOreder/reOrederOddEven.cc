#include <iostream>

using std::cout;
using std::endl;

void reOrederNums(int nums[], int nums_len)
{
    int high = nums_len-1;
    int low = 0;
    int temp;
    while(low < high)
    {
        while(nums[low]%2 == 1)
        {
            low++;
        }
        while(nums[high]%2 == 0)
        {
            high--;
        }
        temp = nums[low];
        nums[low] = nums[high];
        nums[high] = nums [low];
        low++;
        high--;
    }
}

int main()
{
    int nums[10] = {2,6,3,5,8,12,33,4,16,18};
    reOrederNums(nums, 10);
    for(int i=0; i< 10; i++)
        cout << nums[i] << " ";
    return 0;
}
