//POJ1741 树上点对距离<=k的点对数 点分治
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
const int maxn = 20100;
int n, k, Size, root, ans;
int son[maxn],vis[maxn], F[maxn], dis[maxn];
struct edge{
    int v;
    int val;
    edge(int x, int y)
    {
        v = x;
        val = y;
    }
};
vector<edge>m[maxn];
vector<int>d;
void getroot(int u, int fa)
{
    son[u] = 1;
    F[u] = 0;
    int l = m[u].size();
    for (int i = 0; i < l; ++i)
    {
        int v = m[u][i].v;
        if (vis[v] || v == fa) continue;
        getroot(v,u);
        son[u] += son[v];
        F[u] = max(F[u],son[v]);
    }
    F[u] = max(F[u], F[0]-son[u]);
    if (F[u] < F[root]) root = u;
    /*if (F[u] < Size || (F[u] == Size && u < root))
    {
        Size = F[u];
        root = u;
    }*/
    //vis[u] = 1;
}
void getdis(int u, int fa)
{
    d.push_back(dis[u]);
    //son[u] = 1;
    for (int i = 0; i < m[u].size(); ++i)
    {
        int v = m[u][i].v;
        if (v == fa||vis[v]) continue;
        dis[v] = dis[u] + m[u][i].val;
        getdis(v, u);
        //son[u] += son[v];
    }
}
int cal(int u, int val)
{
    int res = 0;
    d.clear();
    dis[u] = val;
    getdis(u, 0);

    sort(d.begin(), d.end());
    int l = 0, r = d.size()-1;
    while (l < r)
    {
        while (d[l]+d[r]>k && l<r) r--;
        res += r-l;
        l++;
    }
    return res;
}
void solve(int u)
{
    vis[u] = 1;
    ans += cal(u, 0);
    for (int i = 0; i < m[u].size(); ++i)
    {
        int v = m[u][i].v;
        if (vis[v]) continue;
        ans -= cal(v, m[u][i].val);
        F[0] = son[u];
        getroot(v, root = 0);
        solve(root);
    }
}
int main()
{
    while (scanf("%d%d", &n, &k) != EOF)
    {
        if (n == 0 && k == 0) break;
        memset(F, 0, sizeof(F));
        memset(vis, 0, sizeof(vis));
        memset(son, 0, sizeof(son));
        for (int i = 1; i <= n; ++i)
            m[i].clear();
        for (int i = 0; i < n-1; ++i)
        {
            int x, y, v;
            scanf("%d%d%d", &x, &y, &v);//边即边权
            m[x].push_back(edge(y,v));
            m[y].push_back(edge(x,v));
        }
        F[0] = n;
        //root = n+1;
        //Size = maxn;
        //printf("%d %d\n",root, Size);
        ans = 0;
        getroot(1, root = 0);
        solve(root);
        printf("%d\n", ans);
    }
    return 0;
}
