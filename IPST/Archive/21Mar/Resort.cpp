#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[1010][1010];

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	int x,y;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&x,&y);
		tbl[x+1][y+1]++;
	}
	for (int i=1;i<=m;i++) {
		for (int j=2;j<=m;j++) {
			tbl[i][j]+=tbl[i][j-1];
		}
	}
	for (int j=1;j<=m;j++) {
		for (int i=2;i<=m;i++) {
			tbl[i][j]+=tbl[i-1][j];
		}
	}
	//for (int i=1;i<=10;i++) {
		//for (int j=1;j<=10;j++) {
			//printf("%d ",tbl[i][j]);
		//}
		//printf("\n");
	//}
	int ans=2e9;
	for (int i=1;i<=m;i++) {
		for (int j=i;j<=m;j++) {
			int lo=1;
			int hi=m+1;
			int mid;
			while (lo<hi) {
				mid=(lo+hi)>>1;
				if (tbl[mid][j]-tbl[mid][i-1]>=k) {
					hi=mid;
				} else {
					lo=mid+1;
				}
			}
			if (hi!=m+1) ans=min(ans,(j-i+1)*hi);
			//printf("%d %d %d\n",i,j,hi);
		}
	}
	printf("%d\n",ans);
	return 0;
}
