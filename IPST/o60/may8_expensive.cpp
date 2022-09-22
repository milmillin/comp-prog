#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

struct ei {
	int to;
	long long w;
};

vector<ei> pth[100100];
int deg[100100];
int bnum[100100];
int cnum[100100];
int bvec[200];
int e1[100100];
int e2[100100];
long long d1[100100];
long long d2[100100];
long long dis[200][200];
bool visit[100100];
int cn=1;

ei chain(int x,int p,int org,long long d) {
	//printf("chain %d\n",x);
	if (bnum[x]) {
		dis[bnum[x]][bnum[org]]=dis[bnum[org]][bnum[x]]=min(dis[bnum[x]][bnum[org]],d);
		//printf("%d %d\n",x,bnum[x]);
		return ei{bnum[x],0};
	}
	//printf("chain %d\n",x);
	cnum[x]=cn;
	visit[x]=true;
	d1[x]=d;
	e1[x]=bnum[org];
	//printf("-- %d %d\n",org,bnum[org]);
	ei tmp;
	tmp.to=0;
	tmp.w=1e18;
	assert(pth[x].size()<=2);
	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		tmp=chain(i.to,x,org,d+i.w);
		d2[x]=i.w;
	}	
	e2[x]=tmp.to;
	d2[x]+=tmp.w;
	return ei{e2[x],d2[x]};
}

int main () {
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		pth[a].push_back(ei{b,c});
		pth[b].push_back(ei{a,c});
		deg[a]++;
		deg[b]++;
	}
	int bn=1;
	for (int i=1;i<=n;i++) {
		if (deg[i]>2) {
			bvec[bn]=i;
			bnum[i]=bn++;	
			d1[i]=d2[i]=0;
			e1[i]=e2[i]=bnum[i];
		}
	}	
	if (bn==1) {
		//assert(false);
		bvec[1]=1;
		bnum[1]=1;
		bn++;
		d1[1]=d2[1]=0;
		e1[1]=e2[1]=1;
	}
	memset(dis,63,sizeof(dis));
	for (int i=1;i<bn;i++) {
		dis[i][i]=0;
		//printf("-- %d\n",bvec[i]);
	}
	for (int i=1;i<bn;i++) {
		for (auto &j:pth[bvec[i]]) {
			if (visit[j.to]) continue;
			chain(j.to,bvec[i],bvec[i],j.w);
			cn++;
		}
	}
	for (int k=1;k<bn;k++) {
		for (int i=1;i<bn;i++) {
			for (int j=1;j<bn;j++) {
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	long long ans;
	for (int i=0;i<q;i++) {
		scanf("%d%d",&a,&b);
		ans=min(min(d1[a]+dis[e1[a]][e1[b]]+d1[b],d1[a]+dis[e1[a]][e2[b]]+d2[b]),min(d2[a]+dis[e2[a]][e1[b]]+d1[b],d2[a]+dis[e2[a]][e2[b]]+d2[b]));
		if (cnum[a]>0&&cnum[b]>0&&cnum[a]==cnum[b]) {
			printf("%lld\n",min(abs(d1[a]-d1[b]),ans));
			continue;
		}
		printf("%lld\n",ans);
		//aa=d1[a]+dis[e1[a]][e1[b]]+d1[b];
		//bb=d1[a]+dis[e1[a]][e2[b]]+d2[b];
		//cc=d2[a]+dis[e2[a]][e1[b]]+d1[b];
		//dd=d2[a]+dis[e2[a]][e2[b]]+d2[b];
		//printf("%d %d %d %d\n",e1[a],e2[a],e1[b],e2[b]);
		//printf("%lld %lld %lld %lld\n",d1[a],d2[a],d1[b],d2[b]);
		//printf("%lld %lld %lld %lld\n",aa,bb,cc,dd);
	}
						
	return 0;
}
