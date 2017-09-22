//hdu6183
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6 + 7;

bool getColor;

struct segTree{
	static const int TREE_MAX = N*4;
	struct node{
		int l, r, val;
	} tree[TREE_MAX];
	int cnt ,root[55];
	void build()
	{
		memset(tree, 0, sizeof(tree));
		memset(root, 0, sizeof(root));
		cnt = 0;
	}

	void add(int p, int v, int &rt, int l, int r){
		if (!rt) tree[rt=++cnt].val = v;
		tree[rt].val = min(tree[rt].val, v);
		if (l == r) return;
		int m = (l+r) >> 1;
		if (p <= m) add(p, v, tree[rt].l, l, m);
		else add(p, v, tree[rt].r, m+1, r);
	}

	void query(int L, int R, int v, int rt, int l, int r){
		if (getColor || !rt) return;
		if (L <= l && r <= R)
		{
			if (tree[rt].val <= v) getColor = 1; return;
		}
		int m = (l+r) >> 1;
		if (L <= m) query(L, R, v, tree[rt].l, l, m);
		if (R >  m) query(L, R, v, tree[rt].r, m+1, r);
	}
} T;

int main()
{
    //freopen("input.txt", "r", stdin);
	int op, x, y, c, X, L, R;
	T.build();
	while (scanf("%d", &op) != EOF)
	{
		if (op == 3) break;
		if (op == 0) T.build();
		else if (op == 1)
		{
			scanf("%d%d%d", &x, &y, &c);
			T.add(y, x, T.root[c], 1, N);
		}
		else if (op == 2)
		{
			int ans = 0;
			scanf("%d%d%d", &X, &L, &R);
			for (int i = 0; i <= 50; ++i)
			{
				getColor = 0;
				T.query(L, R, X, T.root[i], 1, N);
				if (getColor) ans++;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}

