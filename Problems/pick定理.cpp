//核心公式就是Pick定理：S=内点个数+边上点个数/2-1；
#include<stdio.h>
#include<string.h>
#include<math.h>
struct Area
{
int x,y,x1,y1;
}p[1000];
int fabs(int a)
{
if(a<0)
a=-a;
return a;
}
int Euclid_gcd(int a,int b)
{
if(b==0)
return a;
return Euclid_gcd(b,a%b);
}
int fun(int a,int b,int c,int d)
{
return a*d-b*c;
}
int main()
{
int T;
int n;
int i,j,k;
int wd,nd;
int x,y,x1,y1;
float S;
scanf(“%d”,&T);
for(i=1;i<=T;i++)
{
nd=wd=S=0;
p[0].x=p[0].y=0;
scanf(“%d”,&n);
memset(p,0,sizeof(p));
for(j=1;j<=n;j++)
{
scanf(“%d %d”,&x,&y);
x1=fabs(x);
y1=fabs(y);
wd+=Euclid_gcd(x1,y1);
p[j].x=x+p[j-1].x;
p[j].y=y+p[j-1].y;
S+=fun(p[j-1].x,p[j-1].y,p[j].x,p[j].y);
}
S=fabs(S)/2;
nd=S+1-wd/2;
printf(“Scenario #%d:\n%d %d %.1f\n\n”,i,nd,wd,S);
}
return 0;
}