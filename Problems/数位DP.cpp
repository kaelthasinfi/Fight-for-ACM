//²»Òª62
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int dp[10][4];

int solve(int x)
{
    int a[10], i;
    int d = 1;
    int tex = x;
    memset(a, 0, sizeof(a));
    while (x > 0)
    {
        a[d] = x % 10;
        x = x / 10;
        d ++;
    }
    int l = d - 1;
    int flag = 0, ans = 0;
    for (i = l; i >= 1; --i)
    {
        ans += dp[i-1][2] * a[i];
        if (flag)
            ans += dp[i-1][0] * a[i];
        if (!flag && a[i] > 4)
            ans += dp[i-1][0];
        if (!flag && a[i+1] == 6 && a[i] > 2)
            ans += dp[i][1];
        if (!flag && a[i] > 6)
            ans += dp[i-1][1];
        if ((a[i+1] == 6 && a[i] == 2) || a[i] == 4)
            flag = 1;
    }
    return tex - ans;
}

int main()
{
    int n, m, i, ten, tem, d;
    dp[0][0] = 1;
    for (i = 1; i <= 9; ++i)
    {
        dp[i][0] = dp[i-1][0] * 9 - dp[i-1][1];
        dp[i][1] = dp[i-1][0];
        dp[i][2] = dp[i-1][2] * 10 + dp[i-1][1] + dp[i-1][0];
    }
    while ( scanf("%d%d", &n, &m) )
    {
        if (n == 0 || m == 0) break;
        cout << solve(m+1) - solve(n) << endl;
    }
    return 0;
}