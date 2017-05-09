#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#define MAX 1000007
using namespace std;
/*vector<int>p;
int mark[MAX+100];
int init()
{
    int i;
    for (int i = 2; i <= MAX; ++i)
    if (mark[i] == 0)
    {
        mark[i] = 1;
        p.push_back(i);
        int t = i;
        while (t < MAX)
        {
            mark[t] = 1;
            t = t + i;
        }
    }
}*/

////求单值欧拉函数， 可修改为筛法

long long phi(long long x)
{
    long long ans = x;
    long long i;
    long long  l = sqrt(x);
    if (x % 2 == 0)
    {
        ans = ans / 2;
        while (x % 2 == 0)
            x = x / 2;
    }
    i = 3;
    while (i * i <= x)
    {
        if (x % i == 0)
        {
            ans = ans / i;
            ans = ans * (i-1);
            while (x % i == 0)
                x = x / i;
        }
        i = i + 2;
    }
    if (x != 1)
    {
        ans = ans /x;
        ans = ans *(x-1);
    }
    return ans;
}
int main()
{
    long long n;
    //init();
    while (scanf("%lld", &n) != EOF)
    {
        if (n == 0) break;
        printf("%lld\n", phi(n));
    }
    return 0;
}
