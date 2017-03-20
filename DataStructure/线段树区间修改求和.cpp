#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+6;
int n, q;
int a[maxn];
struct node{
    int l, r;
    long long sum, lazy;
    void update(long long x)
    {
        sum += (long long)(r-l+1) * x;
        lazy += x;
    }
}tree[maxn * 4];

void push_up(int x)
{
    tree[x].sum = tree[x << 1].sum + tree[x << 1|1].sum;
}

void push_down(int x)
{
    int lazyval = tree[x].lazy;
    if (lazyval)
    {
        tree[x << 1].update(lazyval);
        tree[x << 1|1].update(lazyval);
        tree[x].lazy = 0;
    }
}

void build(int x, int l, int r)
{
    tree[x].l = l, tree[x].r = r;
    tree[x].sum = tree[x].lazy = 0;
    if (l == r)
    {
        tree[x].sum = a[l];
    }
    else
    {
        int mid = (l+r) / 2;
        build(x << 1, l, mid);
        build(x << 1|1, mid+1, r);
        push_up(x);
    }
}

void update(int x, int l, int r, long long val)
{
    int L = tree[x].l, R = tree[x].r;
    if (l <= L && R <= r)
        tree[x].update(val);
    else
    {
        push_down(x);
        int mid = (L+R) / 2;
        if (l <= mid)
            update(x << 1, l, r, val);
        if (r > mid)
            update(x << 1|1, l, r, val);
        push_up(x);
    }
}

long long query(int x, int l, int r)
{
    int L = tree[x].l, R = tree[x].r;
    if (l <= L && R <= r)
        return tree[x].sum;
    else
    {
        push_down(x);
        long long ans = 0;
        int mid = (L+R) / 2;
        if (l <= mid)
            ans += query(x << 1, l, r);
        if (r > mid)
            ans += query(x << 1|1, l, r);
        push_up(x);
        return ans;
    }
}

int main()
{
    int i;
    cin >> n;
    for (i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    build(1, 1, n);
    scanf("%d", &q);
    for (i = 1; i <= q; ++i)
    {
        int l, r, val;
        scanf("%d%d%d", &l, &r, &val);
        update(1, l, r, val);
        printf("%lld\n", query(1, l, r));
    }
    return 0;
}