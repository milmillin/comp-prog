#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
	int a,b,w;
};

struct ei {
	int to,id;
};

edge e[100100];
vector<ei> pth[100100];

int dis[100100];
int lo[100100];
bool visit[100100];
int time=1;

vector<int> ecycle;

void dfs(int x,int p) {
	dis[x]=lo[x]=time++;
	visit[x]=true;
	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		if (visit[i.to]) {
			lo[x]=min(lo[x],dis[i.to]);
			ecycle.push_back(i.id);
			continue;
		}
		dfs(i.to,x);
		lo[x]=min(lo[x],lo[i.to]);
		if (lo[i.to]<=dis[x]) {
			ecycle.push_back(i.id);
		}
	}
}


int main () {
	int n,q;
	scanf("%d%d",&n,&q);
	for (int i=1;i<=n;i++) {
		scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].w);
		pth[e[i].a].push_back(ei{e[i].b,i});
	}
	dfs(1,1);
	sort(ecycle.begin(),ecycle.end());	
	return 0;
}
