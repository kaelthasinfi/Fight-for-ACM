//筛法求欧拉函数
#include<iostream>
#include<cstdio>
#include<cstring>
const int maxn = 3000000;
using namespace std;
long long phi[maxn+100];
bool mark[maxn+100];

void init()
{
    int i, j;
    for (i = 1; i <= maxn; ++i)
        phi[i] = i;
    for (i = 2; i <= maxn; ++i)
    if (phi[i] == i)
        for (j = i; j <= maxn; j+=i)
            phi[j] = (phi[j]/i)*(i-1);
    /*if (mark[i] == false)
    {
        int j = i;
        while (j <= maxn)
        {
            phi[j] = (phi[j]/i)*(i-1);
            mark[j] = true;
            j = j + i;
        }
    }*/
}
int main()
{
    long long a, b;
    init();
    while (scanf("%lld%lld", &a, &b) != EOF)
    {
        long long ans = 0;
        for (int i = a; i <= b; ++i)
            ans += phi[i];
        printf("%lld\n", ans);
    }
    return 0;
}
