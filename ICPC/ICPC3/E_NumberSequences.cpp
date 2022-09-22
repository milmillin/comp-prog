#include <cstdio>

using namespace std;

long long tbl[1010][1010];

int main () {
	int n;
	scanf("%d",&n);
	bool diff=false;
	for (int i=0;i<n;i++) {
		scanf("%lld",&tbl[0][i]);
		if (i) diff=diff||(tbl[0][i]!=tbl[0][i-1]);
	}
	if (!diff) {
		printf("%lld\n",tbl[0][0]);
		return 0;
	}
	for (int i=1;i<=n;i++) {
		bool dif=false;
		for (int j=0;j<n-i;j++) {
			tbl[i][j]=tbl[i-1][j+1]-tbl[i-1][j];
			if (j) dif=dif||(tbl[i][j]!=tbl[i][j-1]);
		}
		if (!dif) {
			tbl[i][n-i]=tbl[i][n-i-1];
			for (int j=i-1;j>=0;j--) {
				tbl[j][n-j]=tbl[j][n-j-1]+tbl[j+1][n-j-1];
			}
			break;
		}
	}
	printf("%lld\n",tbl[0][n]);
	return 0;
}
