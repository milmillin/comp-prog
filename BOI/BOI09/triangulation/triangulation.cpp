#include <cstdio>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

struct tr {
	int a,b,c;
	int col;

	bool operator== (const tr &r) const {
		return a==r.a&&b==r.b&&c==r.c&&col==r.col;
	}
};

int n;

pair<int,int> order(int a,int b) {
	if (a<b) return {a,b};
	return {b,a};
}

map<pair<int,int>,vector<tr>> mp;

int col[100100];
vector<int> pth[100100];
int par[20][100100];
int dep[100100];
int m;

vector<int> ver[100100];

int build(const tr &x, const tr &p, int d) {
	int id=m++;
	col[id]=x.col;
	ver[x.col].push_back(id);
	dep[id]=d;
	//printf("%d\n",dep[id]);
	for (auto &i:mp[order(x.a,x.b)]) {
		if (i==x) continue;
		if (i==p) continue;
		pth[id].push_back(build(i,x,d+1));
		par[0][pth[id].back()]=id;
	}
	for (auto &i:mp[order(x.a,x.c)]) {
		if (i==x) continue;
		if (i==p) continue;
		pth[id].push_back(build(i,x,d+1));
		par[0][pth[id].back()]=id;
	}
	for (auto &i:mp[order(x.c,x.b)]) {
		if (i==x) continue;
		if (i==p) continue;
		pth[id].push_back(build(i,x,d+1));
		par[0][pth[id].back()]=id;
	}
	return id;
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

int ancdep[100100];
bool del[100100];

int mincut(int x) {
	int cur=ancdep[col[x]];
	int aa;
	for (auto i:pth[x]) {
		aa=mincut(i);
		if (aa<=dep[x]) del[i]=true;	
		cur=min(cur,aa);
	}
	return cur;
}

int cnt(int x) {
	int ans=0;
	for (auto i:pth[x]) {
		if (!del[i]) ans++;
		ans+=cnt(i);
	}
	return ans;
}

int main () {
	//freopen("trian08.in","r",stdin);
	scanf("%d",&n);
	int a,b,c,d;
	for (int i=0;i<n-2;i++) {
		scanf("%d%d%d%d",&a,&b,&c,&d);
		mp[order(a,b)].push_back(tr{a,b,c,d});
		mp[order(a,c)].push_back(tr{a,b,c,d});
		mp[order(b,c)].push_back(tr{a,b,c,d});
	}
	//printf("yay\n");
	int root = build(tr{a,b,c,d},tr{},0);
	
	//printf("--> %d\n",m);
	for (int i=1;i<20;i++) {
		for (int j=0;j<m;j++) {
			par[i][j]=par[i-1][par[i-1][j]];
		}
	}

	for (int i=1;i<=n;i++) {
		if (ver[i].empty()) continue;
		ancdep[i]=ver[i].front();
		for (int j=1;j<(int)ver[i].size();j++) {
			ancdep[i]=lca(ancdep[i],ver[i][j]);
		}
		ancdep[i]=dep[ancdep[i]];
	}
	mincut(root);
	printf("%d\n",cnt(root));
	return 0;
}
