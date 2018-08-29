#include <bits/stdc++.h>
const int maxn=1e5+7;
#define mod 998244353
#define Lson l,m,rt<<1
#define Rson m+1,r,rt<<1|1
typedef long long ll;
using namespace std;
int n;
struct Edge
{
    double l,r,h;
    int flag;
    Edge()=default;
    Edge(double a,double b,double c,int e):l(a),r(b),h(c),flag(e){}
    bool operator < (const Edge &a) const
    {
        return h<a.h;
    }
}edge[maxn*2];
double x[maxn*2];
struct Tree
{
    int l,r;
    double len1,len2;
    int s;
    Tree()=default;
}tree[maxn*3];
void push_up(int rt)
{
    if(tree[rt].s)
    {
        tree[rt].len1=x[tree[rt].r+1]-x[tree[rt].l];
    }
    else if(tree[rt].l==tree[rt].r) tree[rt].len1=0;
    else
    {
        tree[rt].len1=tree[rt<<1].len1+tree[rt<<1|1].len1;
    }

    if(tree[rt].s>1)
    {
        tree[rt].len2=x[tree[rt].r+1]-x[tree[rt].l];
    }
    else if(tree[rt].r==tree[rt].l) tree[rt].len2=0;//叶子节点
    else if(tree[rt].s==1) tree[rt].len2=tree[rt<<1].len1+tree[rt<<1|1].len1;//父亲被完全覆盖一次
    else
    {
        tree[rt].len2=tree[rt<<1].len2+tree[rt<<1|1].len2;
    }
}
void Build(int l,int r,int rt)
{
    tree[rt].l=l,tree[rt].r=r;
    tree[rt].len1=tree[rt].len2=0,tree[rt].s=0;
    if(l==r) return;
    int m=(l+r)>>1;
    Build(Lson);
    Build(Rson);
}
void updata(int L,int R,int v,int l,int r,int rt)
{
    if(L<=l&&R>=r)
    {
        tree[rt].s+=v;
        push_up(rt);
        return;
    }
    int m=(l+r)>>1;
    if(L<=m) updata(L,R,v,Lson);
    if(R>m) updata(L,R,v,Rson);
    push_up(rt);
}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    cin>>T;
    while(T--)
    {
        scanf("%d",&n);
        double x1,y1,x2,y2;
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            edge[i*2-1]=Edge(x1,x2,y1,1);
            edge[i*2]=Edge(x1,x2,y2,-1);
            x[i*2-1]=x1,x[i*2]=x2;
        }
        sort(edge+1,edge+1+2*n);
        sort(x+1,x+1+2*n);
        int tot=unique(x+1,x+1+2*n)-&x[1];
        Build(0,tot-1,1);
        double ans=0.f;
        for(int i=1;i<2*n;i++)
        {
            int l=upper_bound(x+1,x+1+tot,edge[i].l)-&x[1];
            int r=upper_bound(x+1,x+1+tot,edge[i].r)-&x[1]-1;
            //cout<<l<<" "<<r<<endl;
            updata(l,r,edge[i].flag,0,tot-1,1);
            ans+=(edge[i+1].h-edge[i].h)*tree[1].len2;
        }
        printf("%.2lf\n",ans);
    }
    return 0;
}