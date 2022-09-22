#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

vector<int> pth[100100];

bool isArt[100100];
int lo[100100];
int di[100100];
bool visit[100100];
int ti=0;


vector<int> comps[100100];
int compN=0;
int compId[100100];

vector<int> pthBC[100100];
int par[20][100100];
int sz[20][100100];
int dep[100100];

vector<int> stk;
void dfs(int x,int p) {
	lo[x]=di[x]=ti++;
	visit[x]=true;
	stk.push_back(x);
	for (auto i:pth[x]) {
		if (i==p) continue;
		if (visit[i]) {
			lo[x]=min(lo[x],di[i]);
			continue;
		}	
		dfs(i,x);
		lo[x]=min(lo[x],lo[i]);
		if (lo[i]>=di[x]) {
			isArt[x]=di[x]>0||di[i]>1;
			comps[compN].push_back(x);
			while (comps[compN].back()!=i) {
				comps[compN].push_back(stk.back());
				stk.pop_back();				
			}
			compN++;
		}
	}
}


void dfs2(int x,int p,int d) {
	dep[x]=d;
	par[0][x]=p;
	for (auto i:pthBC[x]) {
		if (i==p) continue;
		dfs2(i,x,d+1);
	}
}

int lca(int a,int b) {
	if (dep[a]<dep[b]) swap(a,b);
	int dif=dep[a]-dep[b];
	int ans=0;
	for (int i=0;i<20;i++) {
		if (dif&(1<<i)) {
			ans+=sz[i][a];
			a=par[i][a];
		}
	}
	if (a==b) return ans+sz[0][a];
	for (int i=19;i>=0;i--) {
		if (par[i][a]!=par[i][b]) {
			ans+=sz[i][a];
			ans+=sz[i][b];
			a=par[i][a];
			b=par[i][b];
		}
	}
	ans+=sz[0][a];
	a=par[0][a];
	ans+=sz[0][b];
	b=par[0][b];
	ans+=sz[0][a];
	return ans;
}

int main () {
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		pth[a].push_back(b);
		pth[b].push_back(a);
	}
	dfs(1,1);
	printf("%d\n",compN);

	//if (!stk.empty()) {
		//while (!stk.empty()) {
			//comps[compN].push_back(stk.back());
			//stk.pop_back();
		//}
		//compN++;
	//}
	
	int curId=0;
	for (int i=1;i<=n;i++) {
		if (isArt[i]) {
			sz[0][curId]=0;
			compId[i]=curId++;
		}
	}
	for (int i=0;i<compN;i++) {
		for (auto j:comps[i]) {
			if (!isArt[j]) compId[j]=curId;
			else {
				pthBC[compId[j]].push_back(curId);
				pthBC[curId].push_back(compId[j]);
			}
		}
		sz[0][curId]=comps[i].size()-1;
		curId++;
	}
	dfs2(0,0,0);
	for (int i=1;i<20;i++) {
		for (int j=0;j<curId;j++) {
			par[i][j]=par[i-1][par[i-1][j]];
			sz[i][j]=sz[i-1][j]+sz[i-1][par[i-1][j]];
		}
	}
	for (int i=0;i<q;i++) {
		scanf("%d%d",&a,&b);
		printf("%d\n",lca(compId[a],compId[b])-1);
	}
	return 0;
}
