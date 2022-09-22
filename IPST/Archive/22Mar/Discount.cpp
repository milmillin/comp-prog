#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct edge {
	int from, to,wgt;
};

bool operator< (const edge &a, const edge &b) {
	return a.wgt<b.wgt;
}

vector<edge> ee;
int par[20100];

int findPar(int idx) {
	if (par[idx]==idx) return idx;
	return par[idx]=findPar(par[idx]);
}

void jn(int a,int b) {
	par[findPar(a)]=findPar(b);	
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b,c;
	for (int i=0;i<m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		ee.push_back(edge{a,b,c});
	}
	sort(ee.begin(),ee.end());
	for (int i=0;i<n;i++) {
		par[i]=i;
	}
	int ans=2e9;
	for (int i=0;i<m;i++) {
		if (findPar(ee[i].from)==findPar(ee[i].to)) continue;
		jn(ee[i].from,ee[i].to);
	}
	printf("%d\n",ans+1);
	return 0;
}
