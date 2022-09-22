#include <cstdio>
#include <cassert>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int ord[200][200];
long long dis[200][200];

struct ei {
	int a,b;
	long long w;
};

bool operator< (const ei &a, const ei &b) {
	return a.w<b.w;
}

bool adj[300][300];
int d[300];
int par[300];

int n,m,p,q;
int s,t,nn;
//vector<int> stk;
queue<int> qq;	

bool augment() {
	memset(d,63,sizeof(d));
	memset(par,-1,sizeof(par));
	while (!qq.empty()) qq.pop();
	d[s]=0;
	qq.push(s);
	int now;
	while (!qq.empty()) {
		now=qq.front();
		qq.pop();
		if (now==t) break;
		for (int i=0;i<nn;i++) {
			if (!adj[now][i]) continue;
			if (d[i]<=d[now]+1) continue;
			d[i]=d[now]+1;
			par[i]=now;
			qq.push(i);
		}	
	}
	if (par[t]==-1) return false;
	return true;
}

int work() {
	s=2*p;
	t=2*p+1;	
	nn=2*p+2;

	for (int i=0;i<p;i++) {
		adj[s][i]=true;
		adj[i+p][t]=true;
	}
	//printf("yay\n");
	while (augment()) {
		//printf("--yay\n");
		int cur=t;
		while (par[cur]!=-1) {
			adj[cur][par[cur]]=true;
			adj[par[cur]][cur]=false;
			//printf("%d -> %d\n",par[cur],cur);
			cur=par[cur];
		}
		//for (int i=0;i<nn;i++) {
			//for (int j=0;j<nn;j++) {
				//printf("%d ",adj[i][j]);
			//}
			//printf("\n");
		//}
		//scanf("%d",&x);
	}
	int cnt=0;
	for (int i=0;i<nn;i++) {
		if (adj[i][s]) {
			//printf("-- %d\n",i);
			cnt++;
		}
	}
	return cnt;
}

int main () {
	scanf("%d%d%d%d",&n,&m,&p,&q);
	for (int i=0;i<q;i++) {
		for (int j=0;j<p;j++) {
			scanf("%d",&ord[i][j]);
		}
	}	
	memset(dis,63,sizeof(dis));
	for (int i=0;i<n;i++) dis[i][i]=0;
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);	
		dis[a][b]=c;
		dis[b][a]=c;
	}
	for (int k=0;k<n;k++) {
		for (int i=0;i<n;i++) {
			for (int j=0;j<n;j++) {
				dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
			}
		}
	}

	//for (int i=0;i<n;i++) {
		//for (int j=0;j<n;j++) {
			//printf("%d ",dis[i][j]);
		//}
		//printf("\n");
	//}

	long long ans=0;
	for (int i=1;i<q;i++) {
		vector<ei> aa;
		for (int j=0;j<p;j++) {
			for (int k=0;k<p;k++) {
				aa.push_back(ei{j,k,dis[ord[i-1][j]][ord[i][k]]});
			}
		}	
		sort(aa.begin(),aa.end());
		//int cur=-1;
		//for (int j=0;j<aa.size();j++) {
			//memset(adj,0,sizeof(adj));
			//for (int kk=0;kk<=j;kk++) {
				//adj[aa[kk].a][aa[kk].b+p]=true;
				////printf("add %d %d\n",aa)
			//}
			//int tmp=work();
			////printf("%d\n",tmp);
			//if (tmp==p) {
				//cur=j;
				//break;
			//}
		//}	
		//assert(cur!=-1);
		//ans+=aa[cur].w;
		int hi=aa.size();
		int lo=0;
		int mid;
		while (lo<hi) {
			mid=(lo+hi)>>1;
			memset(adj,0,sizeof(adj));
			for (int kk=0;kk<=mid;kk++) {
				adj[aa[kk].a][aa[kk].b+p]=true;
			}
			int tmp=work();
			if (tmp==p) {
				hi=mid;
			} else {
				lo=mid+1;
			}
		}
		ans+=aa[hi].w;
	}
	printf("%lld\n",ans);
	return 0;
}
