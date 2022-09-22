#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> pth[100100];
int n,q;
int par[20][100100];
int dep[100100];

int cnt[100100];

void dfs(int x,int p,int d) {
	//printf("dfs %d %d\n",x,p);
	par[0][x]=p;
	dep[x]=d;
	for (auto i:pth[x]) {
		if (i==p) continue;
		dfs(i,x,d+1);
	}
}

int lca(int a,int b) {
	if (dep[a]<dep[b]) swap(a,b);
	int dif=dep[a]-dep[b];
	for (int i=0;i<20;i++) {
		if (dif&(1<<i)) {
			a=par[i][a];
		}
	}
	if (a==b) return a;
	for (int i=19;i>=0;i--) {
		if (par[i][a]!=par[i][b]) {
			a=par[i][a];
			b=par[i][b];
		}
	}	
	return par[0][a];
}

int dist(int a,int b) {
	int c=lca(a,b);
	return dep[a]+dep[b]-dep[c]*2;
}

void solve3() {
	dfs(1,1,0);
	for (int i=1;i<20;i++) {
		for (int j=1;j<=n;j++) {
			par[i][j]=par[i-1][par[i-1][j]];
		}
	}
	int t,a,b;
	vector<pair<int,int>> eiei;
	for (int i=0;i<q;i++) {
		scanf("%d",&t);
		if (t==1) {
			scanf("%d%d",&a,&b);
			eiei.push_back({a,b});	
		} else {
			scanf("%d",&a);
			int cnt=0;
			for (auto &j:eiei) {
				if (dist(a,j.first)<=j.second) cnt++;
			}
			printf("%d\n",cnt);
		}
	}	
}


void spread(int x,int p,int d) {
	if (d==0) return;
	//printf("sp %d %d %d\n",x,p,d);
	cnt[x]++;
	for (auto i:pth[x]) {
		if (i==p) continue;
		spread(i,x,d-1);
	}
}

int main () {
	scanf("%d%d",&n,&q);
	int a,b;
	for (int i=1;i<n;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	if (n<=10000) {
		solve3();
		return 0;
	} 
	int t;
	for (int i=0;i<q;i++) {
		scanf("%d",&t);
		if (t==1) {
			scanf("%d%d",&a,&b);
			assert(b<=5);
			spread(a,a,b+1);
		} else {
			scanf("%d",&a);
			printf("%d\n",cnt[a]);
		}
	}
	return 0;
}
