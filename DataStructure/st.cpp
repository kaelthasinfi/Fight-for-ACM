//query max and min in interval
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 50005
using namespace std;
int n, q;
int a[N];
int maxx[N][16], minn[N][16];
void st(int n)
{
	for (int i = 1; i <= n; ++i)
		maxx[i][0] = a[i], minn[i][0] = a[i];
	int k = log(n * 1.0) / log(2.0);
	for (int j = 1; j <= k; ++j)
		for (int i = 1; i+(1<<j)-1 <= n; ++i)
		{
			maxx[i][j] = max(maxx[i][j-1],maxx[i + (1<<(j-1))][j-1]);
			minn[i][j] = min(minn[i][j-1],minn[i + (1<<(j-1))][j-1]);
		}
	return;
}
int getAns(int x, int y)
{
	int k = log(y-x+1.0)/log(2.0);
	return max(maxx[x][k],maxx[y+1-(1<<k)][k])-min(minn[x][k],minn[y+1-(1<<k)][k]);
}
int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	st(n);
	while (q--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%d\n", getAns(x, y));
	}
	return 0;
}
