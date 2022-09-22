#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct edge {
	int a,b,w;
};

bool operator< (const edge &a, const edge &b) {
	return a.w<b.w;
}

vector<edge> edges;

int par[100100];

int findpar(int x) {
	if (par[x]==x) return x;
	return par[x]=findpar(par[x]);
}

struct ei {
	int to,w;
};

vector<ei> pth[100100];

int mod=33331;
int p[20][100100];
int cost[20][100100];
int dep[100100];

int poww(int x) {
	if (x==0) return 1;
	if (x==1) return 2;
	int tmp=poww(x/2);
	tmp*=tmp;
	tmp%=mod;
	if (x%2) return (2*tmp)%mod;
	return tmp;
}
void dfs(int x,int pp,int d) {
	dep[x]=d;
	//p[0][x]=pp;
	for (auto &i:pth[x]) {
		if (i.to==pp) continue;
		p[0][i.to]=x;
		cost[0][i.to]=poww(i.w);
		dfs(i.to,x,d+1);
	}
}

int ask(int a,int b) {
	if (dep[a]<dep[b]) swap(a,b);
	int dif=dep[a]-dep[b];
	int ans=0;
	for (int i=0;i<20;i++) {
		if ((1<<i)&dif) {
			ans+=cost[i][a];
			ans%=mod;
			a=p[i][a];
		}
	}
	if (a==b) return ans;
	for (int i=19;i>=0;i--) {
		if (p[i][a]!=p[i][b]) {
			ans+=cost[i][a];
			ans+=cost[i][b];
			ans%=mod;
			a=p[i][a];
			b=p[i][b];
		}
	}
	ans+=cost[0][a];
	ans+=cost[0][b];
	ans%=mod;
	return ans;
}


int main () {
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	int a,b,w;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&w);
		edges.push_back(edge{a,b,w});
	}
	sort(edges.begin(),edges.end());
	for (int i=1;i<=n;i++) par[i]=i;
	for (auto &e:edges) {
		if (findpar(e.a)==findpar(e.b)) continue;
		pth[e.a].push_back(ei{e.b,e.w});
		pth[e.b].push_back(ei{e.a,e.w});	
		par[findpar(e.a)]=findpar(e.b);
	}
	dfs(1,1,1);
	for (int i=1;i<20;i++) {
		for (int j=1;j<=n;j++) {
			p[i][j]=p[i-1][p[i-1][j]];
			cost[i][j]=(cost[i-1][j]+cost[i-1][p[i-1][j]])%mod;
		}
	}	
	for (int i=0;i<q;i++) {
		scanf("%d%d",&a,&b);
		printf("%d\n",ask(a,b));
	}
	return 0;
}
