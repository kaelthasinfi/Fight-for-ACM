//ÈýÔª»·
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
#include<vector>
#include<map>
#include<algorithm>
#define N 100000
using namespace std;
struct edge{
    int x;
    int y;
};
vector<int>node[N+5];
edge e[100100];

int cmp(int x, int y)
{
    return x < y;
}
long long tot;
int n, m, i;
int deg[100100];
int main()
{
    int t;
    cin >> t;
    for (int o = 0; o < t; ++o)
    {
        tot = 0;
        memset(deg, 0, sizeof(deg));
        scanf("%d%d", &n, &m);
        for (i = 1; i <= n; ++i)
            node[i].clear();
        for (i = 0; i < m; ++i)
        {
            scanf("%d%d", &e[i].x, &e[i].y);
            int x = e[i].x;
            int y = e[i].y;
            deg[x]++;
            deg[y]++;
        }

        for (i = 0; i < m; ++i)
        {
            int x = e[i].x;
            int y = e[i].y;
            if (deg[x] > deg[y])
                node[y].push_back(x);
            else if (deg[x] < deg[y])
                node[x].push_back(y);
            else
            {
                if (x < y)
                    node[x].push_back(y);
                else node[y].push_back(x);
            }
        }
        for (i = 1; i <= n; ++i)
            sort(node[i].begin(), node[i].end(), cmp);
        /*for (i = 1; i <= n; ++i)
        {
            for (int j = 0; j < node[i].size(); ++j)
                cout << node[i][j] << " ";
            cout << endl;
        }

        */
        for (i = 0; i < m; ++i)
        {
            int x, y;
            x = e[i].x;
            y = e[i].y;
            int l1 = node[x].size();
            int l2 = node[y].size();
            int p = 0, q = 0;
            while (p < l1 && q < l2)
            {
                if (node[x][p] == node[y][q])
                {
                    tot++;
                    p++;
                    q++;
                }
                else if (node[x][p] < node[y][q])
                    p++;
                else q++;
            }
        }
        cout << tot << endl;
    }
    return 0;
}
