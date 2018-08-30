//poj 3695
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
const int maxn=1<<21;
#define mod 998244353
#define Lson l,m,rt<<1
#define Rson m,r,rt<<1|1
#define inf 0x3f3f3f3f
typedef long long ll;
using namespace std;
int n,m;
struct Point
{
    int x1,y1,x2,y2;
}p[25];
int query[maxn];
int ans[maxn];
void dfs(int x1,int y1,int x2,int y2,int pos,int sgn,int sta)
{
    if(x1>=x2||y1>=y2) return;
    if(pos==n+1)
    {
        if(sta){
        for(int i=1;i<=m;i++)
        {
            if((query[i]&sta)==sta)
            {
                ans[query[i]]+=sgn*(x2-x1)*(y2-y1);
            }
        }
        }
        return;
    }
    int xx1=max(x1,p[pos+1].x1),yy1=max(y1,p[pos+1].y1);
    int xx2=min(x2,p[pos+1].x2),yy2=min(y2,p[pos+1].y2);
    dfs(x1,y1,x2,y2,pos+1,sgn,sta);
    dfs(xx1,yy1,xx2,yy2,pos+1,-sgn,sta|(1<<pos));
    return;
}

int main(int argc, char const *argv[])
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
    int Case=0;
    while(scanf("%d%d",&n,&m)!=EOF&&(n+m))
    {
        memset(query,0,sizeof(query));
        memset(ans,0,sizeof(ans));
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d%d",&p[i].x1,&p[i].y1,&p[i].x2,&p[i].y2);
        }
        for(int i=1;i<=m;i++)
        {
            int num;
            scanf("%d",&num);
            while(num--)
            {
                int x;
                scanf("%d",&x);
                query[i]|=(1<<(x-1));
            }   
        }
        dfs(0,0,inf,inf,0,-1,0);
        printf("Case %d:\n",++Case);
        for(int i=1;i<=m;i++)
        {
            printf("Query %d: %d\n",i,ans[query[i]]);
        }
        printf("\n");
    }
    return 0;
}
