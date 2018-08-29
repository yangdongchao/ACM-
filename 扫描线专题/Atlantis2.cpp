//边更新边建树算法
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <math.h>
#include <stack>
const int maxn=1e5+7;
#define mod 998244353
#define Lson l,m,rt<<1
#define Rson m+1,r,rt<<1|1
typedef long long ll;
using namespace std;
int n;
struct Edeg
{
    double l,r,h;
    int flag;
    Edeg()=default;
    Edeg(double a,double b,double c,int d):l(a),r(b),h(c),flag(d){}
}edge[maxn*3];
bool cmp(Edeg a, Edeg b)
{
    return a.h<b.h;
}
double x[maxn*2];
struct Tree
{
    int l,r,lazy;
    double len;
}tree[maxn<<2];

void push_up(int rt,int l,int r)
{
    if(tree[rt].lazy)
    {
        tree[rt].len=(x[r+1]-x[l]);
    }
    else if(l==r) tree[rt].len=0;
    else tree[rt].len=tree[rt<<1].len+tree[rt<<1|1].len;
}
void updata(int L,int R,int v,int l,int r,int rt)
{
    if(L<=l&&R>=r)
    {
        tree[rt].lazy+=v;
        push_up(rt,l,r);
        return;
    }
    int m=(l+r)>>1;
    if(L<=m) updata(L,R,v,Lson);
    if(R>m) updata(L,R,v,Rson); 
    push_up(rt,l,r);
}
int main(int argc, char const *argv[])
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int kca=0;
    while(scanf("%d",&n)!=EOF&&n)
    {
        int k=0,m=0;
        for(int i=1;i<=n;i++)
        {
            double x1,y1,x2,y2;
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            x[++k]=x1,x[++k]=x2;
            edge[++m]=Edeg(x1,x2,y1,1);
            edge[++m]=Edeg(x1,x2,y2,-1);
        }
        for(int i=1;i<=m;i++)
        {
            tree[i].len=tree[i].lazy=0;
        }
        sort(edge+1,edge+m+1,cmp);
        sort(x+1,x+k+1);
        int tot=unique(x+1,x+k+1)-&x[1];
        double ans=0.f;
        for(int i=1;i<2*n;i++)
        {
            //cout<<edge[i].l<<" "<<edge[i].r<<endl;
            int l=lower_bound(x+1,x+tot+1,edge[i].l)-&x[0];
            int r=lower_bound(x+1,x+tot+1,edge[i].r)-&x[0]-1;//维护左闭右开区间
            //cout<<l<<" "<<r<<endl;
            updata(l,r,edge[i].flag,0,tot-1,1);
            ans+=(edge[i+1].h-edge[i].h)*tree[1].len;
        }
        printf("Test case #%d\n",++kca);
        printf("Total explored area: %.2f\n\n",ans);
    }
    return 0;
}
