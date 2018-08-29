#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
#define N 2005
using namespace std;
struct P{ll s,e,h,f;}p[N];
struct Tree{ll sum,c;}t[N<<5];
int x[N],n,m,ans;
int cmp(const P &a,const P &b){
    return a.h<b.h;
}
void init(){
    n=m=ans=0;
    memset(p,0,sizeof p);
    memset(t,0,sizeof t);
    x[0]=-1;
}
void pushUp(ll rt,ll l,ll r){
    if(t[rt].c)t[rt].sum=x[r+1]-x[l];
    else if(l==r)t[rt].sum=0;
    else t[rt].sum=t[rt<<1].sum+t[rt<<1|1].sum;
}
void update(ll s,ll e,ll rt,ll l,ll r,ll v){
    if(s<=l&&r<=e) t[rt].c+=v;
    else {
        if(l>e||r<s)return;
        ll m=l+r>>1;
        update(s,e,rt<<1,l,m,v);
        update(s,e,rt<<1|1,m+1,r,v);
    }
    pushUp(rt,l,r);
}
int main()
{
    int a,b,c,d;
    init();
    while(cin>>a>>b>>c>>d){
            if(a<0)break;
        while(a>=0){
            p[++n].s=a,p[n].e=c,p[n].h=b,p[n].f=1;x[n]=a;
            p[++n].s=a,p[n].e=c,p[n].h=d,p[n].f=-1;x[n]=c;
            cin>>a>>b>>c>>d;
        }
        sort(x+1,x+1+n);
        for(int i=1;i<=n;i++)
            if(x[i]!=x[i-1])x[++m]=x[i];

        sort(p+1,p+1+n,cmp);
        for(int i=1;i<n;i++){
            int l=lower_bound(x,x+m,p[i].s)-x;
            int r=lower_bound(x,x+m,p[i].e)-x-1;

            update(l,r,1,1,m,p[i].f);
            ans+=t[1].sum*(p[i+1].h-p[i].h);
        }
        cout<<ans<<endl;
        init();
    }
    return 0;
}