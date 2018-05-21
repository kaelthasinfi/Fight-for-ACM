//k维空间中离所给点最近的m个点，并按顺序输出。
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <set>
#include <vector>
#include <map>
#define ll long long

using namespace std;

const int N=50007;
const int K=6;

int n,m;

struct point{
    int a[K];
    int div;  // 按哪个维度划分
    bool lef;  // 是否是叶子节点
    ll dis;  // 离询问点的距离。注意这个在读入建树时不会用到，在进入队列时才用到
    void print(){
        printf("%d",a[0]);
        for (int i=1;i<m;i++) 
            printf(" %d",a[i]);
        puts("");
    }
    bool operator < (const point &t) const{
        return dis<t.dis;
    }
    point(){}
    point(point &t,ll d){
        for (int i=0;i<m;i++) a[i]=t.a[i];
        dis=d;
    }
}p[N],tar;

int cmp_NO;
inline bool cmp(point x,point y){
    return x.a[cmp_NO]<y.a[cmp_NO];
}

inline ll dis(point x,point y){
    ll ret=0;
    for (int i=0;i<m;i++) 
        ret+=(x.a[i]-y.a[i])*(x.a[i]-y.a[i]);
    return ret;
}

inline void bulid_kdt(int L,int R,int d){
    if (L>R) return;
    int mid=(L+R)>>1;
    cmp_NO=d;
    nth_element(p+L,p+mid,p+R+1,cmp);
    p[mid].div=d;
    if (L==R){
        p[L].lef=true;
        return;
    }
    bulid_kdt(L,mid-1,(d+1)%m);
    bulid_kdt(mid+1,R,(d+1)%m);
}

priority_queue<point> que;
int num,nownum;
ll ans;

inline void find_kd(int L,int R){
    if (L>R) return;
    
    int mid=(L+R)>>1;
    ll d=dis(p[mid],tar);
    if (p[mid].lef){
        if (nownum<num){
            nownum++;
            que.push(point(p[mid],d));
            ans=max(ans,d);
        }
        else if (ans>d){
            que.pop();
            que.push(point(p[mid],d));
            ans=que.top().dis;
        }
        return;
    }

    int t=tar.a[p[mid].div]-p[mid].a[p[mid].div];
    if (t>0){
        find_kd(mid+1,R);
        if (nownum<num){
            nownum++;
            que.push(point(p[mid],d));
            ans=max(ans,d);
            find_kd(L,mid-1);
        }
        else {
            if (ans>d){
                que.pop();
                que.push(point(p[mid],d));
                ans=que.top().dis;
            }
            if (ans>t*t) 
                find_kd(L,mid-1);
        }
    }
    else {
        find_kd(L,mid-1);
        if (nownum<num){
            nownum++;
            que.push(point(p[mid],d));
            ans=max(ans,d);
            find_kd(mid+1,R);
        }
        else{
            if (ans>d){
                que.pop();
                que.push(point(p[mid],d));
                ans=que.top().dis;
            }
            if (ans>t*t) 
                find_kd(mid+1,R);
        }
    }
}

inline void put(){
    if (que.empty()) return;
    point pp=que.top();
    que.pop();
    put();
    pp.print();
}

int main(){
    while (~scanf("%d%d",&n,&m)){
        for (int i=0;i<n;i++){
            for (int j=0;j<m;j++) 
                scanf("%d",&p[i].a[j]);
            p[i].lef=false;
        }

        bulid_kdt(0,n-1,0);  // 这一步相当于将原数组重新排了个序，先访问到的点放在中间

        int q;
        scanf("%d",&q);
        while (q--){
            for (int i=0;i<m;i++)
                scanf("%d",&tar.a[i]);
            while (!que.empty()) que.pop();
            scanf("%d",&num);
            nownum=0;
            ans=-1;
            find_kd(0,n-1);
            printf("the closest %d points are:\n",num);
            put();
        }
    }
    return 0;
}