//POJ1655 Ê÷µÄÖØÐÄ
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
const int maxn = 20100;
int n, Size, ans;
int son[maxn],vis[maxn];
vector<int>m[maxn];
void dfs(int u)
{
    son[u] = 0;
    vis[u] = 1;
    int l = m[u].size();
    int balance = 0;
    for (int i = 0; i < l; ++i)
    {
        int v = m[u][i];
        if (vis[v]) continue;
        dfs(v);
        son[u] += (son[v]+1);
        balance = max(balance, son[v]+1);
    }
    balance = max(balance, n-son[u]-1);
    if (balance < Size || (balance == Size && u < ans))
    {
        Size = balance;
        ans = u;
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            m[i].clear();
            son[i] = 0;
            vis[i] = 0;
        }
        for (int i = 0; i < n-1; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            m[x].push_back(y);
            m[y].push_back(x);
        }
        ans = n+1;
        Size = maxn;
        dfs(1);
        printf("%d %d\n",ans, Size);
    }
    return 0;
}
