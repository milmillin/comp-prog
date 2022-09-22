#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int tbl[1000][1000];

void f() {
	int r,c;
	scanf("%d%d",&r,&c);
	memset(tbl,127,sizeof(tbl));
	int ans=2e9;
	for (int i=0;i<r;i++) {
		for (int j=1;j<=c;j++) {
			scanf("%d",&tbl[i][j]);
			if (i) tbl[i][j]+=min(tbl[i-1][j],min(tbl[i-1][j-1],tbl[i-1][j+1]));
			if (i==r-1) ans=min(ans,tbl[i][j]);
		}
	}
	printf("%d\n",ans);
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
