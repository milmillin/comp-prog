#include <cstdio>

using namespace std;

long long tbl[400][400];
bool unused[400][400];

int main() {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		for (int j=0;j<n;j++) {
			scanf("%lld",&tbl[i][j]);
		}
	}
	long long ans=0;
	for (int k=0;k<n;k++) {
		for (int i=0;i<n;i++) {
			for (int j=0;j<n;j++) {
				if (tbl[i][k]+tbl[k][j]<tbl[i][j]) {
					printf("-1\n");
					return 0;
				}
				if (tbl[i][k]+tbl[k][j]==tbl[i][j]) {
					if (i!=k&&k!=j) {
						//printf("%d %d %d\n",i,j,k);
						unused[i][j]=true;
					}
				}	
			}
		}
	}
	for (int i=0;i<n;i++) {
		for (int j=i+1;j<n;j++) {
			if (!unused[i][j]) ans+=tbl[i][j];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
