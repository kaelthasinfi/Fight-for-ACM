#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAX 1000007
using namespace std;
vector<int>p;
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
}
int phi(long long x)
{
    long long ans = x;
    int i = 0;
    int l = p.size();
    while (p[i] <= x && i < l)
    {
        if (x % p[i] == 0)
        {
            ans = ans * (p[i]-1);
            ans = ans / p[i];
            while (x % p[i] == 0)
                x = x / p[i];
        }
        i++;
    }
    return ans;
}
int main()
{
    long long n;
    init();
    while (scanf("%lld", &n) != EOF)
    {
        if (n == 0) break;
        printf("%d\n", phi(n));
    }
    return 0;
}
