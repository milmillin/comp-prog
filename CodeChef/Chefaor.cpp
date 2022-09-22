#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

int tbl[40][50100];

int orSum(int from,int to) {
	int x=0;
	for (int i=0;i<30;i++) {
		if (tbl[i][to]-tbl[i][from-1]) {
			x+=(1<<i);
		}
	}
	return x;
}

long long mic[5010][5010];

void solve(int d,int l,int r,int ll,int rr) {
	if (l>=r) return;
	int m=(l+r)>>1;
	int id=-1;
	int tmp;
	mic[d][m]=0;
	for (int i=ll;i<min(rr,m+1);i++) {
		tmp=orSum(i+1,m);
		if (mic[d-1][i]+tmp>=mic[d][m]) {
			mic[d][m]=mic[d-1][i]+tmp;
			id=i;
		}
	}
	if (l+1==r) return;
	solve(d,l,m,ll,id+1);
	solve(d,m+1,r,id,rr);
}

void f() {
	int n,k;
	scanf("%d%d",&n,&k);
	int x;
	memset(tbl,0,sizeof(tbl));
	for (int i=1;i<=n;i++) {
		scanf("%d",&x);
		for (int j=0;j<30;j++) {
			if (x&(1<<j)) tbl[j][i]++;
			tbl[j][i]+=tbl[j][i-1];
		}
	}
	for (int i=1;i<=n;i++) {
		mic[1][i]=orSum(1,i);
	}
	for (int i=2;i<=k;i++) {
		solve(i,1,n+1,1,n+1);
	}
	printf("%lld\n",mic[k][n]);
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
