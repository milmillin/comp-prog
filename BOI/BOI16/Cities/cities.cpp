#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int imp[50];

struct edge {
	int a,b;
	int wgt;

	bool operator< (const edge &r) const {
		return wgt<r.wgt;
	}
};

int par[100100];

int findpar(int x) {
	if (par[x]==x) return x;
	return par[x]=findpar(par[x]);
}

struct ei {
	int to,wgt;
};

vector<ei> pth[100100];

int pa[20][100100];
long long wgt[20][100100];
int dep[100100];

bool mark[100100];

void dfs(int x,int p) {
	dep[x]=dep[p]+1;
	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		pa[0][i.to]=x;
		wgt[0][i.to]=i.wgt;
		dfs(i.to,x);	
	}
}

int lca(int a,int b) {
	if (dep[a]<dep[b]) swap(a,b);
	int dif=dep[a]-dep[b];
	for (int i=0;i<20;i++) {
		if (dif&(1<<i)) {
			a=pa[i][a];
		}
	}
	if (a==b) return a;
	for (int i=19;i>=0;i--) {
		if (pa[i][a]!=pa[i][b]) {
			a=pa[i][a];
			b=pa[i][b];
		}
	}
	return pa[0][a];
}

int main () {
	int n,k,m;
	scanf("%d%d%d",&n,&k,&m);
	for (int i=0;i<k;i++) {
		scanf("%d",&imp[i]);
	}
	vector<edge> ed;
	ed.reserve(m);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		ed.push_back(edge{a,b,c});
	}
	sort(ed.begin(),ed.end());
	for (int i=1;i<=n;i++) {
		par[i]=i;
	}
	for (auto &e:ed) {
		if (findpar(e.a)==findpar(e.b)) continue;
		par[findpar(e.a)]=findpar(e.b);
		pth[e.a].push_back(ei{e.b,e.wgt});
		pth[e.b].push_back(ei{e.a,e.wgt});
	}
	pa[0][1]=1;
	dfs(1,1);
	for (int i=1;i<20;i++) {
		for (int j=1;j<=n;j++) {
			pa[i][j]=pa[i-1][pa[i-1][j]];
			wgt[i][j]=wgt[i-1][j]+wgt[i-1][pa[i-1][j]];
		}
	}	
	int cur;
	for (int i=0;i<k;i++) {
		for (int j=i+1;j<k;j++) {
			c=lca(imp[i],imp[j]);
			cur=imp[i];
			while (cur!=c) {
				mark[cur]=true;
				cur=pa[0][cur];
			}	
			cur=imp[j];
			while (cur!=c) {
				mark[cur]=true;
				cur=pa[0][cur];
			}
		}
	}
	long long ans=0;
	for (int i=1;i<=n;i++) {
		if (mark[i]) ans+=wgt[0][i];
	}	
	printf("%lld\n",ans);
	return 0;
}
