//hdu6184求有一边重合的两个三元环组成的四边形个数
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
#define N 100000
using namespace std;
vector<int>node[N+5];
bool mark[N+5];
int link[N+5];
set<long long>edge;
int i, sq;
long long n, m, tot;
void init()
{
    memset(mark, 0, sizeof(mark));
    memset(link, 0, sizeof(link));
    for (i = 1; i <= n; ++i)
        node[i].clear();
    edge.clear();
}
int main()
{
    //freopen("input.txt", "r", stdin);
    while (scanf("%lld%lld", &n, &m) != EOF)
    {
        tot = 0;
        sq = sqrt(m);
        init();
        for (i = 0; i < m; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            node[x].push_back(y);
            node[y].push_back(x);
            edge.insert((long long)y*n+x);
            edge.insert((long long)x*n+y);
        }
        for (int i = 1; i <= n; ++i)
        {
            int x = i;
            mark[x] = 1;
            for (int j = 0; j < node[x].size(); ++j)
            {
                int y = node[x][j];
                link[y] = x;
            }
            for (int j = 0; j < node[x].size(); ++j)
            {
                long long sum = 0;
                int y = node[x][j];
                if (mark[y]) continue;
                if (node[y].size() <= sq)
                {
                    for (int k = 0; k < node[y].size(); ++k)
                        if (link[node[y][k]] == x)
                            sum++;
                }
                else
                {
                    for (int k = 0; k < node[x].size(); ++k)
                    {
                        long long z = node[x][k];
                        long long tmp = z*n+(long long)y;
                        if (edge.count(tmp))  sum++;
                    }
                }
                tot += sum*(sum-1)/2;
            }
        }
        printf("%lld\n", tot);
    }
    return 0;
}
