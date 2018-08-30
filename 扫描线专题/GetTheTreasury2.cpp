#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
struct node{
    int L,R,h,d;
}a[maxn*2];

struct Edge{
    int x1,y1,z1,x2,y2,z2;
}b[maxn];
int one[maxn*8],more[maxn*8],z[maxn*2],mark[maxn*8],t[maxn*2],two[maxn*8];

bool cmp(node u,node v){
    if(u.h==v.h)
        return u.d>v.d;
    return u.h<v.h;
}

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

void pushup(int rt,int l,int r){
    if(mark[rt]>=3){
        more[rt]=t[r+1]-t[l];
        two[rt]=t[r+1]-t[l];
        one[rt]=t[r+1]-t[l];
    }
    else if(mark[rt]==2){
        more[rt]=one[rt<<1]+one[rt<<1|1];
        two[rt]=t[r+1]-t[l];
        one[rt]=t[r+1]-t[l];
    }
    else if(mark[rt]==1){
        more[rt]=two[rt<<1]+two[rt<<1|1];
        two[rt]=one[rt<<1]+one[rt<<1|1];
        one[rt]=t[r+1]-t[l];
    }
    else{
        more[rt]=more[rt<<1]+more[rt<<1|1];
        two[rt]=two[rt<<1]+two[rt<<1|1];
        one[rt]=one[rt<<1]+one[rt<<1|1];
    }
}

int L,R,d;

void update(int l,int r,int rt){
    if(L<=l&&R>=r){
        mark[rt]+=d;
        pushup(rt,l,r);
        return ;
    }
    int m=(l+r)>>1;
    if(L<=m)
        update(lson);
    if(R>m)
        update(rson);
    pushup(rt,l,r);
}

int main(){
    int n,_;
    scanf("%d",&_);
    for(int case1=1;case1<=_;case1++){
        long long ans=0;
        int tot=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d%d%d%d",&b[i].x1,&b[i].y1,&b[i].z1,&b[i].x2,&b[i].y2,&b[i].z2),z[++tot]=b[i].z1,z[++tot]=b[i].z2;
        sort(z+1,z+tot+1);
        tot=unique(z+1,z+tot+1)-z-1;
        for(int i=1;i<tot;i++){
            int sz=0;
            for(int j=1;j<=n;j++)
                if(b[j].z1<=z[i]&&b[j].z2>=z[i+1]){
                    a[++sz]=(node){b[j].x1,b[j].x2,b[j].y1,1};
                    a[++sz]=(node){b[j].x1,b[j].x2,b[j].y2,-1};
                    t[sz-1]=b[j].x1,t[sz]=b[j].x2;
                }
            sort(t+1,t+sz+1);
            int m=unique(t+1,t+sz+1)-t-1;
            sort(a+1,a+sz+1,cmp);
            memset(mark,0,sizeof(mark));
            memset(one,0,sizeof(one));
            memset(two,0,sizeof(two));
            memset(more,0,sizeof(more));
            for(int j=1;j<sz;j++){
                L=lower_bound(t+1,t+m+1,a[j].L)-t,R=lower_bound(t+1,t+m+1,a[j].R)-t-1,d=a[j].d;
                update(1,m,1);
                ans+=1LL*more[1]*(a[j+1].h-a[j].h)*(z[i+1]-z[i]);
            }
        }
        printf("Case %d: %lld\n",case1,ans);
    }
    return 0;
}