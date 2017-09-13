#include<cstdio>
#include<cstring>
const int maxn = 310;
int a[maxn][maxn];
int link[maxn];
bool used[maxn];
int p, n;
bool dfs(int u)
{
	int v;
	for (v = 1; v <= n; ++v)
		if (a[u][v] == 1 && !used[v])
		{
			used[v] = 1;
			if (link[v] == -1 || dfs(link[v]))
			{
				link[v] = u;
				return true;
			}
		}
	return false;
}
int hungary()
{
	int ans = 0;
	int u;
	memset(link, -1, sizeof(link));
	for (u = 1; u <= p; ++u)
	{
		memset(used, false, sizeof(used));
		if (dfs(u))
			ans++;
	}
	return ans;
}
int main()
{
	int t, i, j;
	scanf("%d", &t);
	while (t--)
	{
		memset(a, 0, sizeof(a));
		scanf("%d%d", &p, &n);
		for (i = 1; i <= p; ++i)
		{
			int x;
			scanf("%d", &x);
			for (j = 1; j <= x; ++j)
			{
				int y;
				scanf("%d", &y);
				a[i][y] = 1;
			}
		}
		if (hungary() == p)
		{
//			printf("%d\n", hungary());
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
//			printf("%d\n", hungary());
		}
	}
	return 0;
}
