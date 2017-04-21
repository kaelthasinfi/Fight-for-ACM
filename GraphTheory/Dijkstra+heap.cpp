#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define MAX 0x7fffffff
using namespace std;
const int maxn = 10100;
int n, m;
struct node{
    int v;
    int cost;
    node(){};
    node(int a, int b) {v=a;cost=b;}
};
bool operator<(node a, node b)
{
    if (a.cost == b.cost) return a.v < b.v;
    return a.cost > b.cost;
}
vector<node>edge[maxn];
priority_queue<node>Q;
int dis[maxn];
int dijkstra(int s, int t)
{
    int i;
    while (!Q.empty()) Q.pop();
    for (i = 1; i <= n; ++i)
        dis[i] = MAX;
    dis[s] = 0;
    Q.push(node(s, 0));
    while (!Q.empty())
    {
        node x = Q.top();
        Q.pop();
        for (i = 0; i < edge[x.v].size(); ++i)
        {
            int v = edge[x.v][i].v;
            if (dis[v] > dis[x.v]+edge[x.v][i].cost)
            {
                dis[v] = dis[x.v]+edge[x.v][i].cost;
                Q.push(node(v, dis[v]));
            }
        }
        //for (i = 1; i <= n; ++i)
        //    cout << dis[i] << " ";
        //cout << endl;
    }
    return dis[t];
}
int main()
{
    int i;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        if (n == 0 && m == 0) break;
        for (i = 1; i <= n; ++i)
            edge[i].clear();
        for (i = 0; i < m; ++i)
        {
            int x, y, v;
            scanf("%d%d%d", &x, &y, &v);
            edge[x].push_back(node(y,v));
            edge[y].push_back(node(x,v));
        }
        printf("%d\n", dijkstra(1, n));
    }
    return 0;
}
