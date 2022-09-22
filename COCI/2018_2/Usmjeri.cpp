#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

vector<int> pth[300100];
int par[20][300100];
int dep[300100];
int high[300100];
int col[300100];

struct pp{
	int idx,col;
};

vector<pp> ee[300100];

void init(int idx,int p,int d) {
	dep[idx]=d;
	par[0][idx]=p;
	for (auto i:pth[idx]) {
		if (i==p) continue;
		init(i,idx,d+1);
	}
}

int lca(int a,int b) {
	if (dep[a]<dep[b]) swap(a,b);
	for (int i=19;i>=0;i--) {
		if (dep[par[i][a]]>=dep[b]) a=par[i][a];
	}
	//printf("as %d %d\n",a,b);
	if (a==b) return a;
	for (int i=19;i>=0;i--) {
		if (par[i][a]!=par[i][b]) {
			a=par[i][a];
			b=par[i][b];
		}
	}
	return par[0][a];
}

int connect(int idx,int p) {
	for (auto i:pth[idx]) {
		if (i==p) continue;
		int tmp = connect(i,idx);
		high[idx]=min(high[idx],tmp);
		if (tmp<dep[idx]) {
			//printf("add %d %d %d\n",idx,i,tmp);
			ee[idx].push_back(pp{i,0});
			ee[i].push_back(pp{idx,0});
		}
	}
	return high[idx];
}

bool dfs(int idx,int c) {
	//printf("%d %d %d\n",idx,c,col[idx]);
	if (col[idx]!=-1) return col[idx]==c;
	col[idx]=c;
	for (auto i:ee[idx]) {
		if (!dfs(i.idx,c^i.col)) return false;
	}
	return true;
}

int mod = 1000000007;

int f() {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	init(1,1,1);
	//for (int i=1;i<=n;i++) {
		//printf("----- %d %d\n",i,dep[i]);
	//}
	for (int i=1;i<20;i++) {
		for (int j=1;j<=n;j++) {
			par[i][j]=par[i-1][par[i-1][j]];
			//printf("%d ",par[i][j]);
		}
		//printf("\n");
	}
	for (int i=1;i<=n;i++) {
		high[i]=dep[i];
	}
	while (m--) {
		scanf("%d%d",&a,&b);
		int c = lca(a,b);
		//printf("-- %d\n",c);
		high[a]=min(high[a],dep[c]);
		high[b]=min(high[b],dep[c]);
		if (a!=c&&b!=c) {
			ee[a].push_back(pp{b,1});
			ee[b].push_back(pp{a,1});
		}
	}
	//printf("yay\n");
	connect(1,1);
	//printf("eiei\n");
	memset(col,-1,sizeof(col));
	int ans=1;
	for (int i=2;i<=n;i++) {
		//printf("%d\n",i);
		if (col[i]!=-1) continue;
		if (!dfs(i,0)) return 0;
		ans *=2;
		ans %= mod;	
	}
	return ans;
}

int main() {
	printf("%d\n",f());	
	return 0;
}
