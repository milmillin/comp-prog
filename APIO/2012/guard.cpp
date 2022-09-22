#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int max_n=1e5+5;
const int max_m=1e5+5;
const int max_tree=max_n*4;
const int inf=2e9;

int n,m,k,x,y,ty,cnt,A,B,tot,now,l,r,mid,k1,k2,number;
int point[max_n],pre[max_n],nxt[max_n],num[max_n],f[max_m],g[max_m],hsh[max_n];
int sum[max_tree],delta[max_tree];
struct hp{int x,y;}a[max_m],b[max_m],interval[max_m];

inline void update(int now){sum[now]=sum[now<<1]+sum[now<<1|1];}
inline void pushdown(int now,int l,int r,int mid){
    if (delta[now]){
        sum[now<<1]=mid-l+1; delta[now<<1]=1;
        sum[now<<1|1]=r-mid; delta[now<<1|1]=1;
        delta[now]=0;
    }
}
inline void interval_change(int now,int l,int r,int lrange,int rrange){
    int mid=(l+r)>>1;
    if (lrange<=l&&r<=rrange){
        sum[now]=r-l+1;
        delta[now]=1;
        return;
    }
    if (lrange<=mid) interval_change(now<<1,l,mid,lrange,rrange);
    if (mid+1<=rrange) interval_change(now<<1|1,mid+1,r,lrange,rrange);
    update(now);
}
inline int query(int now,int l,int r,int x){
    int mid=(l+r)>>1;
    if (l==r) return sum[now];
    pushdown(now,l,r,mid);
    if (x<=mid) return query(now<<1,l,mid,x);
    else return query(now<<1|1,mid+1,r,x);
}
inline int cmp(hp a,hp b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
int main(){
    scanf("%d%d%d",&n,&k,&m);
    for (int i=1;i<=m;++i){
        scanf("%d%d%d",&x,&y,&ty);
        if (ty==0) interval_change(1,1,n,x,y);
        else a[++A].x=x,a[A].y=y;
    }
    for (int i=1;i<=n;++i){
        point[i]=query(1,1,n,i)^1;
        if (point[i]) num[i]=++cnt,hsh[cnt]=i;
    }
    if (cnt==k){
        for (int i=1;i<=n;++i)
          if (num[i]) printf("%d\n",i);
        return 0;
    }

    for (int i=1;i<=n;++i) if (!point[i]) pre[i]=pre[i-1]; else pre[i]=i;
    for (int i=n;i>=1;--i) if (!point[i]) nxt[i]=nxt[i+1]; else nxt[i]=i;
    for (int i=1;i<=A;++i){
        a[i].x=nxt[a[i].x]; a[i].y=pre[a[i].y];
        if (a[i].x<=0||a[i].x>n||a[i].y<=0||a[i].y>n||a[i].x>a[i].y) continue;
        b[++B].x=num[a[i].x]; b[B].y=num[a[i].y];
    }

    sort(b+1,b+B+1,cmp);
    for (int i=B,j;i>=1;i=j){
        j=i-1;
        while (b[j].y>=b[i].y) j--;
        interval[++tot].x=b[i].x,interval[tot].y=b[i].y;
    }
    sort(interval+1,interval+tot+1,cmp);
	for (int i=1;i<=tot;i++) {
		printf("%d %d\n",interval[i].x,interval[i].y);
	}
	printf("--\n");

    int mx=0,mn=inf;
    for(int i=1;i<=tot;i++)
        if(interval[i].x>mx)f[i]=f[i-1]+1,mx=interval[i].y;
        else f[i]=f[i-1];
    for(int i=tot;i;i--)
        if(interval[i].y<mn)g[i]=g[i+1]+1,mn=interval[i].x;
        else g[i]=g[i+1];

	for (int i=1;i<=tot;i++) {
		printf("%d %d\n",f[i],g[i]);
	}
	printf("--\n");

    bool flag=false;
    int i=2; now=1;
    while (i<=tot+1){
        if (interval[now].y-1<interval[now].x){
            flag=true;
            printf("%d\n",hsh[interval[now].y]);
            while (i<=tot&&interval[i].x<=interval[now].y) i++;
            now=i;
            i++;
            continue;
        }
        l=1; r=now-1; mid=0; k1=0;
        while (l<=r){
            mid=(l+r)>>1;
            if (interval[mid].y<interval[now].y-1) k1=mid,l=mid+1;
            else r=mid-1;
        }
        l=now+1; r=tot; mid=0; k2=0;
        while (l<=r){
            mid=(l+r)>>1;
            if (interval[mid].x>interval[now].y-1) k2=mid,r=mid-1;
            else l=mid+1;
        }
		printf("%d %d %d\n",now,k1,k2);
        if (f[k1]+g[k2]+1>k) flag=true,printf("%d\n",hsh[interval[now].y]);

        while (i<=tot&&interval[i].x<=interval[now].y) i++;
        now=i;
        i++;
    }
    if (!flag) printf("-1\n");
}
