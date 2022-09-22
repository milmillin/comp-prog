#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

struct edge {
	int a,b,c;
};

bool operator< (const edge &a, const edge &b) {
	return a.c<b.c;
}


int par[100100];

int findpar(int x) {
	if (par[x]==x) return x;
	return par[x]=findpar(par[x]);
}

struct ei {
	int to,w;
};

vector<ei> pth[100100];

long long dis[100100];
long long mx[100100];

void dfs(int x,int p,int m) {
	for (auto &i:pth[x]) {
		if (i.to==p) continue;
		dis[i.to]=dis[x]+i.w;
		dfs(i.to,x,max(m,i.w));
	}	
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int s,t;
	scanf("%d%d",&s,&t);
	vector<edge> e;
	int a,b,c;
	long long ans=0;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		e.push_back(edge{a,b,c});
		ans+=c;
	}
	sort(e.begin(),e.end());
	for (int i=0;i<n;i++) par[i]=i;
	for (auto &ee:e) {
		if (findpar(ee.a)==findpar(ee.b)) continue;
		par[findpar(ee.a)]=findpar(ee.b);
		//ans-=ee.c;
		pth[ee.a].push_back(ei{ee.b,ee.c});
		pth[ee.b].push_back(ei{ee.a,ee.c});
	}
	//printf("%lld\n",ans);
	dfs(s,-1,0);
	ans-=dis[t];
	ans+=mx[t];
	printf("%lld %lld\n",dis[t],mx[t]);
	printf("%lld\n",ans);
	return 0;
}
