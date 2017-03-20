#include<bits/stdc++.h>
using namespace std;
const int maxn = 50050;
int s[maxn];
struct node{
    int l, r;
    int ls, rs, ms;
}tree[maxn * 4];

int n, m, top;
char w[10];
int max(int x, int y)
{
    if (x < y) return y;
    else return x;
}

void push_up(int x)
{
    tree[x].ls = tree[x << 1].ls;
    tree[x].rs = tree[x << 1|1].rs;
    tree[x].ms = max(max(tree[x << 1].ms, tree[x << 1|1].ms),
                     (tree[x << 1].rs+tree[x << 1|1].ls));
}

void build(int x, int l, int r)
{
    tree[x].l = l;
    tree[x].r = r;
    tree[x].ls = tree[x].rs = tree[x].ms = r-l+1;
    if (l < r)
    {
        int mid = (l+r) / 2;
        build(x << 1, l, mid);
        build(x << 1|1, mid+1, r);
    }
}

void update(int x, int t, int val)
{
    int L = tree[x].l, R = tree[x].r;
    if (L == R)
    {
        tree[x].ls = tree[x].rs = tree[x].ms = val;
    }
    else
    {
        int mid = (L+R)/2;
        if (t <= mid)
            update(x << 1, t, val);
        else
            update(x << 1|1, t, val);
        push_up(x);
        if (tree[x << 1].rs == mid-L+1)
            tree[x].ls += tree[x << 1|1].ls;
        if (tree[x << 1|1].ls == R-mid)
            tree[x].rs += tree[x << 1].rs;
    }
}

int query(int x, int t)
{
    int L = tree[x].l, R = tree[x].r;
    if (L == R || tree[x].ms == 0) return tree[x].ms;
    if (tree[x].ms == R-L+1)
        return tree[x].ms;
    int mid = (L+R)/2;
    if (t <= mid)
    {
        if (t >= tree[x << 1].r - tree[x << 1].rs + 1)
            return //query(x << 1, t)+query(x << 1|1, mid+1);
            tree[x << 1].rs + tree[x << 1|1].ls;
        else
            return query(x << 1, t);
    }
    else if (t > mid)
    {
        if (t <= tree[x << 1|1].ls + tree[x << 1|1].l - 1)
            return //query(x << 1|1, t)+query(x << 1, mid);
            tree[x << 1|1].ls + tree[x << 1].rs;
        else
            return query(x << 1|1, t);
    }

}

int main()
{
    int i;
    while (scanf("%d%d", &n, &m) != EOF)
    {

    build(1, 1, n);
    top = 0;
    for (i = 0; i < m; ++i)
    {
        scanf("%s", &w);
        if (w[0] == 'D')
        {
            int x;
            scanf("%d", &x);
            s[top++] = x;
            update(1, x, 0);
        }
        if (w[0] == 'Q')
        {
            int x;
            scanf("%d", &x);
            cout << query(1, x) << endl;
        }
        if (w[0] == 'R')
        {
            int x = s[--top];

            update(1, x, 1);
        }
    }
    }
    return 0;
}
