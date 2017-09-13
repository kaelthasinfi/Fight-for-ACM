//整体二分求kth number
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>

#define INF 1000000000
const int maxn = 100005;
int n, m;
int c[maxn], ans[maxn], tmp[2*maxn];
struct node{
    int l, r, k, val;
    int cur, index;
    int kind;
}q[2*maxn], q1[maxn], q2[maxn];

void init()
{
    memset(c, 0, sizeof(c));
    memset(tmp, 0, sizeof(tmp));
    for (int i = 1; i <= m+n; ++i)
        q[i].cur = q1[i].cur = q2[i].cur = 0;
}

inline int lowbit(int x)
{
    return x&-x;
}

inline void update(int x, int v)
{
    while (x <= n)
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
void divide(int s, int t, int l, int r)
{
    if (s>t) return;
    if (l==r)
    {
        for (int i = s; i <= t; ++i)
            if (q[i].kind == 2)
                ans[q[i].index] = l;
        return;
    }
    int mid = (l+r)>> 1;
    int num1=0, num2=0, flag1=0, flag2=0;
    for (int i = s; i <= t; ++i)
    {
        if (q[i].kind == 1)
        {
            if (q[i].val <= mid) update(q[i].index, 1), q1[num1++] = q[i];
            else q2[num2++] = q[i];
        }
        else if (q[i].kind == 2)
        {
            tmp[i] = query(q[i].r) - query(q[i].l-1);
            if (q[i].cur + tmp[i] >= q[i].k)
                q1[num1++] = q[i], flag1 = 1;
            else
                q[i].cur += tmp[i], q2[num2++] = q[i], flag2 = 1;
        }
    }
    for (int i = s; i <= t; ++i)
    {
        if (q[i].kind == 1 && q[i].val <= mid) update(q[i].index, -1);
    }
    for (int i = 0; i < num1; i++) q[s+i] = q1[i];
    for (int i = 0; i < num2; i++) q[s+num1+i] = q2[i];
    if (flag1) divide(s, s+num1-1, l, mid);
    if (flag2) divide(s+num1, t, mid+1, r);
}
int main()
{
    while (scanf("%d%d", &n, &m) != EOF)
    {
        init();
        int cnt = 1;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d",&q[cnt].val);
            q[cnt].kind = 1;
            q[cnt].index = i;
            cnt++;
        }
        for (int i = 1; i <= m; ++i)
        {
            q[cnt].index = i;
            scanf("%d%d%d", &q[cnt].l, &q[cnt].r, &q[cnt].k);
            q[cnt].kind = 2;
            cnt++;
        }
        divide(1, cnt-1, -INF, INF);
        for (int i = 1; i <= m; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}
