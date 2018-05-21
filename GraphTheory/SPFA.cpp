#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=300001;
const int inf =0x7ffffff;
struct edge
{
    int from,to,w,next;
}e[1000001];
int head[maxn];
int vis[maxn];
int dist[maxn], cnt[maxn];
int n,m,t;
void add(int i,int j,int w)
{
    e[t].from=i;
    e[t].to=j;
    e[t].w=w;
    e[t].next=head[i];
    head[i]=t++;
}
bool spfa(int s)
{
    queue <int> q;
    for(int i=1;i<=n;i++)
    	dist[i]=inf;
    memset(vis,false,sizeof(vis));
    q.push(s);
    dist[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=head[u];i!=-1;i=e[i].next)
        {
            int v=e[i].to;
            if(dist[v]>dist[u]+e[i].w)
            {
                dist[v]=dist[u]+e[i].w;
                if(!vis[v])
                {
                    vis[v]=true;
                    q.push(v);
                }
				cnt[v]++;
				if (cnt[v] > n) return false;
            }
        }
    }
	return true;
}
int main()
{
    int a,b,c,s,e;
    scanf("%d%d",&n,&m);
    t=0;
    memset(head,-1,sizeof(head));
    while(m--)
    {
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }
    scanf("%d%d",&s,&e);
	int res = spfa(s);
	if (res) 
	{
    	if(dist[e]==inf) printf("UN\n");
    	else printf("%d\n",dist[e]);
	}
	else printf("UN\n");
    return 0;
}
