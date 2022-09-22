#include <cstdio>
#include <algorithm>

using namespace std;

long long tbl[40100];
long long mic[110][40100];

void solve(int d,int l,int r,int ll,int rr) {
	if (l>=r) return;
	int m=(l+r)>>1;
	int id=-1;
	mic[d][m]=1e18;
	for (int i=ll;i<min(rr,m+1);i++) {
		if (mic[d-1][i]+(tbl[m]-tbl[i])*(m-i)<mic[d][m]) {
			mic[d][m]=mic[d-1][i]+(tbl[m]-tbl[i])*(m-i);
			id=i;
		}
	}
	if (l+1==r) return;
	solve(d,l,m,ll,id+1);
	solve(d,m+1,r,id,rr);
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	m++;
	for (int i=1;i<=n;i++) {
		scanf("%lld",&tbl[i]);
		tbl[i]+=tbl[i-1];
	}
	for (int i=1;i<=n;i++) {
		mic[1][i]=tbl[i]*i;
	}
	for (int i=2;i<=m;i++) {
		solve(i,1,n+1,1,n+1);
	}
	//for (int i=1;i<=m;i++) {
		//for (int j=1;j<=n;j++) {
			//printf("%d ",mic[i][j]);
		//}
		//printf("\n");
	//}
	printf("%lld\n",mic[m][n]);
	return 0;
}
