# 一、基础算法

## 1、排序

### （1）快排

输入举例：

```c++
5
3 1 2 4 5
```

输出：

```c++
1 2 3 4 5
```

代码：

```c++
#include <iostream>

using namespace std;

const int N = 1e6 + 10;
int q[N];
int n;

void quick_sort(int q[], int l, int r) {
    if (l >= r) return; //只有一个元素必有序
    
    int x = q[ l + r >> 1];//确定分界元素
    int i = l - 1, j = r + 1; //确定左右边界,从首尾元素两侧开始
    while(i < j) { //左指针和右指针重合跳出循环
        do i++; while(q[i] < x);//左边元素均小于x
        do j--; while(q[j] > x);//右边元素均大于x
        if (i < j) swap(q[i], q[j]);//左边大于x元素与右边小于x元素交换
    }
    quick_sort(q, l, j), quick_sort(q, j+1, r);//迭代划分
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &q[i]);
    
    quick_sort(q, 0, n - 1);
    for (int i = 0; i < n; ++i) printf("%d ", q[i]);
}
```

### （2）归并

```c++
#include <iostream>

using namespace std;

const int N = 1e8 + 10;
int q[N];
int n;

void merge_sort(int q[], int l, int r) {
    if (l >= r) return;
    
    int mid = l + r >> 1;
    merge_sort(q, l, mid);
    merge_sort(q, mid + 1, r);
    
    int i = l, j = mid + 1, k = 0, temp[r - l + 1];
    while(i <= mid && j <= r) {
        if (q[i] <= q[j]) temp[k++] = q[i++];
        else temp[k++] = q[j++];
    }
    
    while(i <= mid) temp[k++] = q[i++];
    while(j <= r) temp[k++] = q[j++];
    
    for(k=0, i=l; i<=r; ++i, ++k) q[i] = temp[k];
}

int main() {
    scanf("%d", &n);
    for(int i=0; i<n; ++i) scanf("%d", &q[i]);
    merge_sort(q, 0, n-1);
    for(int i=0; i<n; ++i) printf("%d ", q[i]);
    return 0;
}
```

## 2、二分

### （1）整数二分

```c++
bool check(int x) {/* ... */} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid]和[mid + 1, r]时使用：
int bsearch_1(int l, int r)
{
    while (l < r)
    {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;    // check()判断mid是否满足性质
        else l = mid + 1;
    }
    return l;
}
// 区间[l, r]被划分成[l, mid - 1]和[mid, r]时使用：
int bsearch_2(int l, int r)
{
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}
```

### （2）浮点二分

```c++
bool check(double x) {/* ... */} // 检查x是否满足某种性质

double bsearch_3(double l, double r)
{
    const double eps = 1e-6;   // eps 表示精度，取决于题目对精度的要求
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    return l;
}
```

