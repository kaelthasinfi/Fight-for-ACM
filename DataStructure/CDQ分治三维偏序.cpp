//CDQ分治 三维偏序问题
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 100010;
int n;
struct node{
    int x, y, z;
    int id;
}a[maxn], b[maxn];
int c[maxn], ans[maxn];
inline int lowbit(int x)
{
    return x&-x;
}
inline void update(int x, int v)
{
    while (x <= maxn)
    {
        c[x] += v;
        x += lowbit(x);
    }
}
inline int query(int x)
{
    int ans = 0;
    while (x > 0)
    {
        ans += c[x];
        x -= lowbit(x);
    }
    return ans;
}
int cmp(node x, node y)
{
    if (x.z == y.z)
    {
        if (x.y == y.y) return x.x < y.x;
        return x.y < y.y;
    }
    return x.z < y.z;
}
void divide(int l, int r)
{
    if (l == r) return;
    int mid = (l+r) >> 1;
    divide(l, mid);
    divide(mid+1, r);
    int j = l, k = mid+1;
    for (int i = l; i <= r; ++i)
    {
        if ((a[j].y <= a[k].y || k > r) && j <= mid)
        {
            b[i] = a[j++];
            update(b[i].x, 1);
        }
        else
        {
            b[i] = a[k++];
            ans[b[i].id] += query(b[i].x);
        }
    }
    for (int i = l; i <= r; ++i)
    {
        if (i <= mid)
            update(a[i].x, -1);
        a[i] = b[i];
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(c, 0, sizeof(c));
        memset(ans, 0, sizeof(ans));
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
            a[i].id = i;
        }
        sort(a+1, a+n+1, cmp);
        for (int i = n-1; i >= 1; --i)
            if (a[i].x == a[i+1].x && a[i].y == a[i+1].y && a[i].z == a[i+1].z)
                ans[a[i].id] = ans[a[i+1].id]+1;
        divide(1, n);
        for (int i = 1; i <= n; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}
