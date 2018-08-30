// hdu 3642
#include <bits/stdc++.h>
const int maxn=1e5+7;
#define mod 998244353
#define Lson l,m,rt<<1
#define Rson m+1,r,rt<<1|1
typedef long long ll;
using namespace std;
int n;
int x[maxn*2],z[maxn*2];
struct Edge
{
    int l,r,h;
    int flag;
    Edge()=default;
    Edge(int a,int b,int c,int e):l(a),r(b),h(c),flag(e){}
    bool operator < (const Edge &a) const
    {
        return h<a.h;
    }
}edge[maxn*3];
struct Point
{
    int x,y,z;
    Point()=default;
    Point(int a,int b,int c):x(a),y(b),z(c){}
}p[maxn*3];

struct Tree
{
    int l,r,s;
    int len1,len2,len3;
}tree[maxn<<2];
void Build(int l,int r,int rt)
{
    tree[rt].l=l,tree[rt].r=r,tree[rt].s=0;
    tree[rt].len1=tree[rt].len2=tree[rt].len3=0;
    if(l==r) return;
    int m=(l+r)>>1;
    Build(Lson);
    Build(Rson);
}
void push_up(int rt)
{
    int l=tree[rt].l,r=tree[rt].r;
    int lazy=tree[rt].s;
    if(lazy>=3)
    {
        tree[rt].len3=x[r+1]-x[l];
        tree[rt].len1=tree[rt].len2=x[r+1]-x[l];
    }
    else if(lazy==2)
    {
        tree[rt].len3=tree[rt<<1].len1+tree[rt<<1|1].len1;
        tree[rt].len2=x[r+1]-x[l];
        tree[rt].len1=x[r+1]-x[l];
    }
    else if(lazy==1)
    {
        tree[rt].len3=tree[rt<<1].len2+tree[rt<<1|1].len2;
        tree[rt].len2=tree[rt<<1].len1+tree[rt<<1|1].len1;
        tree[rt].len1=x[r+1]-x[l];
    }
    else
    {
        tree[rt].len3=tree[rt<<1].len3+tree[rt<<1|1].len3;
        tree[rt].len2=tree[rt<<1].len2+tree[rt<<1|1].len2;
        tree[rt].len1=tree[rt<<1].len1+tree[rt<<1|1].len1;
    }
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
int main(int argc, char const *argv[])
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T,Case=0;
    cin>>T;
    while(T--)
    {
        scanf("%d",&n);
        int x1,y1,z1,x2,y2,z2;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
            x[2*i-1]=x1,x[2*i]=x2;
            z[2*i-1]=z1,z[2*i]=z2;
            p[2*i-1]=Point(x1,y1,z1);
            p[2*i]=Point(x2,y2,z2);
        }
        if(n<3)
        {
            printf("Case %d: 0\n",++Case);
            continue;
        }
        sort(x+1,x+1+2*n);
        int totx=unique(x+1,x+1+2*n)-&x[1];
        sort(z+1,z+1+2*n);
        int totz=unique(z+1,z+1+2*n)-&z[1];
        ll ans=0;
        for(int i=1;i<totz;i++)
        {
            int k=0;
            for(int j=1;j<=2*n;j+=2)
            {
                if(p[j].z<=z[i]&&p[j+1].z>=z[i+1])
                {
                    edge[++k]=Edge(p[j].x,p[j+1].x,p[j].y,1);
                    edge[++k]=Edge(p[j].x,p[j+1].x,p[j+1].y,-1);
                }
            }
            sort(edge+1,edge+1+k);
            Build(1,totx,1);
            ll ansxy=0;
            for(int j=1;j<k;j++)
            {
                int l=upper_bound(x+1,x+1+totx,edge[j].l)-&x[1];
                int r=upper_bound(x+1,x+1+totx,edge[j].r)-&x[1]-1;
                updata(l,r,edge[j].flag,1,totx,1);
                ansxy+=1ll*tree[1].len3*1ll*(edge[j+1].h-edge[j].h);
            }
            ans+=(ll)ansxy*(ll)(z[i+1]-z[i]);
        }
        printf("Case %d: ",++Case);
        printf("%I64d\n",ans);
    }
    return 0;
}
