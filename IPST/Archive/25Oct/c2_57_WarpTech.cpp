#include <cstdio>
#include <algorithm>

using namespace std;

struct edge {
	int a,b,wgt;
};

bool operator< (const edge &a, const edge &b) {
	return a.wgt<b.wgt;
}

edge tbl[100100];
int ans[5010];
int par[5010];

int findpar(int idx) {
	if (par[idx]==idx) return idx;
	return par[idx]=findpar(par[idx]);
}

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&tbl[i].a,&tbl[i].b,&tbl[i].wgt);
	}
	sort(tbl,tbl+m);
	for (int i=0;i<n;i++) {
		par[i]=i;
	}
	int maxx=0;
	int cmp=n-1;
	for (int i=0;i<m;i++) {
		if (findpar(tbl[i].a)==findpar(tbl[i].b)) continue;
		par[findpar(tbl[i].a)]=findpar(tbl[i].b);
		maxx=max(maxx,tbl[i].wgt);
		ans[cmp]=maxx;
		cmp--;
	}
	int x;
	for (int i=0;i<k;i++) {
		scanf("%d",&x);
		printf("%d\n",ans[x]);
	}
	return 0;
}
