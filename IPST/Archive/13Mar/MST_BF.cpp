#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
	int x,y;
};

struct edge {
	int from,to;
	long long wgt;
};

long long dis(const point &a, const point &b) {
	return (long long)(a.x-b.x)*(a.x-b.x)+(long long)(a.y-b.y)*(a.y-b.y);
}

bool cmp (const edge &a, const edge &b) {
	return a.wgt<b.wgt;
}

int par[100100];

int findPar(int idx) {
	if (par[idx]==idx) return idx;
	return par[idx]=findPar(par[idx]);
}

void jn(int i,int j) {
	par[findPar(i)]=findPar(j);
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		par[i]=i;
	}
	//int x,y;
	vector<point>tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d%d",&tbl[i].x,&tbl[i].y);
	}
	if (n>10000) return 0;
	vector<edge> e;
	for (int i=0;i<n;i++) {
		for (int j=i+1;j<n;j++) {
			e.push_back(edge{i,j,dis(tbl[i],tbl[j])});
		}
	}
	sort(e.begin(),e.end(),cmp);
	long long ans=0;
	for (int i=0;i<(int)e.size();i++) {
		if (findPar(e[i].from)==findPar(e[i].to)) continue;
		jn(e[i].from,e[i].to);
		ans+=e[i].wgt;
	}
	printf("%lld\n",ans);
	return 0;
}
