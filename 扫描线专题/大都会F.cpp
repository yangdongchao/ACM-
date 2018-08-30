// 2018上海大都会 F colcor it
#include<math.h>
#include<stdio.h>
#include<algorithm>
#include <iostream>
using namespace std;

const int maxn=1e5+7;
#define mod 998244353
#define Lson l,m,rt<<1
#define Rson m+1,r,rt<<1|1
typedef long long ll;
using namespace std;
int n,m;
struct circle
{
    int x,y,r;
}p[500];
struct Point
{
    int l,r;
    bool operator < (const Point &a) const
    {
        if(l==a.l) return r < a.r;
        return l < a.l;
    }
}L[1005];
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int q;
        int ans=0;
        scanf("%d%d%d",&n,&m,&q);
        for(int i=0;i<q;i++)
        {
            scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].r);
        }
        for(int i=0;i<n;i++)
        {
            int cnt=0,w,h;
            for(int j=0;j<q;j++)
            {
                if(abs(i-p[j].x)>p[j].r) continue;
                w=abs(i-p[j].x);
                h=floor(sqrt(p[j].r*p[j].r-w*w));
                L[++cnt].l=max(0,p[j].y-h);
                L[cnt].r=min(m-1,p[j].y+h);
            }
            sort(L+1,L+1+cnt);
            if(cnt) ans+=L[1].r-L[1].l+1;
            for(int j=2;j<=cnt;j++)
            {
                if(L[j-1].r>=L[j].l)
                {
                    L[j].l=L[j-1].r+1;
                }
                if(L[j].r>=L[j].l)
                {
                    ans+=L[j].r-L[j].l+1;
                }
                L[j].r=max(L[j-1].r,L[j].r);
            }
        }
        printf("%d\n",n*m-ans);
    }
    return 0;
}
