#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int maxn = 100100;
int n, s, k;
int dp[maxn];
int a[maxn];
struct node{
	int l, r;
	int max, min;
}tree1[maxn * 4], tree2[maxn * 4];
int maxx(int x, int y)
{
	if (x > y) return x;
	else return y;
}
int minn(int x, int y)
{
	if (x < y) return x;
	else return y;
}
void push_up(int x)
{
	tree1[x].max = maxx(tree1[x<<1].max,tree1[x<<1|1].max);
	tree1[x].min = minn(tree1[x<<1].min,tree1[x<<1|1].min);
}

void push_up2(int x)
{
	tree2[x].max = maxx(tree2[x<<1].max,tree2[x<<1|1].max);
	tree2[x].min = minn(tree2[x<<1].min,tree2[x<<1|1].min);
}


void build(int x, int l, int r)
{
	tree1[x].l = l, tree1[x].r = r;
	if (l == r)
	{
		tree1[x].max = tree1[x].min = a[l];
	}
	else
	{
		int mid = (l+r) / 2;
		build(x << 1, l, mid);
		build(x << 1|1, mid+1, r);
		push_up(x);
	}
}

void build2(int x, int l, int r)
{
	tree2[x].l = l, tree2[x].r = r;
	if (l == r)
	{
		return;	
	}
	else
	{
		int mid = (l+r) / 2;
		build2(x << 1, l, mid);
		build2(x << 1|1, mid+1, r);
	}
}

void update(int x, int r, int val)
{
	int L = tree2[x].l, R = tree2[x].r;
	if (L == R)
	{
		tree2[x].min = tree2[x].max = val;
		return;
	}
	int mid = (L+R)/2;
	if (r <= mid)
		update(x<<1, r, val);
	else if (r > mid)
		update(x<<1|1, r, val);
	push_up2(x);
}

int query(int x, int l, int r)
{
	int L = tree1[x].l, R = tree1[x].r;
	if (l <= L && R <= r)
		return tree1[x].max;
	else
	{
		int ans = -(1 << 30);
		int mid = (L+R) / 2;
		if (l <= mid)
			ans = maxx(ans, query(x << 1, l, r));
		if (r > mid)
            ans = maxx(ans, query(x << 1|1, l, r));
        return ans;
    }
}

int query2(int x, int l, int r)
{
	int L = tree1[x].l, R = tree1[x].r;
	if (l <= L && R <= r)
		return tree1[x].min;
	else
	{
		int ans = (1 << 30);
		int mid = (L+R) / 2;
		if (l <= mid)
			ans = minn(ans, query2(x << 1, l, r));
		if (r > mid)
            ans = minn(ans, query2(x << 1|1, l, r));
        return ans;
    }
}


int query3(int x, int l, int r)
{
	if (l > r)
		return INF;
	if (l <= tree2[x].l && tree2[x].r <= r)
	{
		return tree2[x].min;
	}
	int ans = (1 << 30);
	int mid = (tree2[x].l+tree2[x].r) >> 1;
	if (l <= mid)
		ans = minn(ans, query3(x << 1, l, r));
	if (mid < r)
		ans = minn(ans, query3(x << 1|1, l, r));
	return ans;
}

int main()
{
    int i;
    cin >> n >> s >> k;
    for (i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
	build(1, 1, n);
	build2(1, 1, n);
	int ans = 0;
	for (i = 1 ; i <= n; ++i)
	{
		int l = 1, r = i;
		while (l < r)
		{
			int mid = (l+r) >> 1;
			if (query(1, mid, i) - query2(1, mid, i) <= s)
				r = mid;
			else 
				l = mid+1;	
		}
//		cout << l << " ";
		dp[i] = query3(1, l, i-k+1)+1;
		update(1, i+1, dp[i]);
		//cout << query3(1,i+1,i+1) << " " ;
	}
//	cout << endl;
//	for (i = 1; i <= n; ++i)
//		cout << dp[i] << " " ;
//	cout << endl;
	if (dp[n] >= 1<<29)
		puts("-1");
	else printf("%d\n", dp[n]);
    return 0;
}
