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
int mi,mx;
int n;
struct Edeg
{
    double l,r,h;
    int flag;
    Edeg()=default;
    Edeg(double a,double b,double c,int d):l(a),r(b),h(c),flag(d){}
    bool operator < (const Edeg &a) const
    {
        return h<a.h;
    }
}edge[maxn*3];
struct Tree
{
    int l,r;
    double len;
    int lazy;
    bool lc,rc;
    int num;
}tree[maxn<<2];
void Build(int l,int r,int rt)
{
    tree[rt].l=l,tree[rt].r=r;
    tree[rt].lazy=tree[rt].lc=tree[rt].rc=0;
    tree[rt].num=tree[rt].len=0;
    if(l==r) return;
    int m=(l+r)>>1;
    Build(Lson);
    Build(Rson);
}
void push_up(int rt)
{
    if(tree[rt].lazy)
    {
        tree[rt].len=tree[rt].r-tree[rt].l+1;
        tree[rt].lc=tree[rt].rc=1;
        tree[rt].num=1;
    }
    else if(tree[rt].l==tree[rt].r)
    {
        tree[rt].len=tree[rt].num=0;
        tree[rt].lc=tree[rt].rc=0;
    }
    else
    {
        tree[rt].len=tree[rt<<1].len+tree[rt<<1|1].len;
        tree[rt].lc=tree[rt<<1].lc,tree[rt].rc=tree[rt<<1|1].rc;
        tree[rt].num=tree[rt<<1].num+tree[rt<<1|1].num-(tree[rt<<1].rc&tree[rt<<1|1].lc);
    }
}
void updata(int L,int R,int v,int l,int r,int rt)
{
    if(L<=l&&R>=r)
    {
        tree[rt].lazy+=v;
        push_up(rt);
        return;
    }
    int m=(l+r)>>1;
    if(L<=m) updata(L,R,v,Lson);
    if(R>m)  updata(L,R,v,Rson);
    push_up(rt);
}

int main(int argc, char const *argv[])
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    double x1,y1,x2,y2;
    while(scanf("%d",&n)!=EOF)
    {
        mi=maxn,mx=-maxn;
        for(int i=0;i<n;i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            edge[i*2]=Edeg(x1,x2,y1,1);
            edge[i*2+1]=Edeg(x1,x2,y2,-1);
            if(x1>mx) mx=x1;
            if(x2>mx) mx=x2;
            if(x1<mi) mi=x1;
            if(x2<mi) mi=x2;
        }
        sort(edge,edge+2*n);
        double ans=0;
        double last=0;
        Build(mi,mx-1,1);//有个0
        for(int i=0;i<2*n;i++)
        {
            updata(edge[i].l,edge[i].r-1,edge[i].flag,mi,mx-1,1);
            cout<<tree[1].len<<" " <<last<<endl;
            ans+=fabs(tree[1].len-last);
            ans+=(edge[i+1].h-edge[i].h)*2*tree[1].num;
            cout<<tree[1].num<<endl;
            last=tree[1].len;
        }
        printf("%.0f\n",ans);
    }
    return 0;
}
