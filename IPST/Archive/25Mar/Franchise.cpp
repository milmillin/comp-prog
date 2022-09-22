#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[1010];
int mic[1010][1010][40];


int main () {
	int n,k,m;
	scanf("%d%d%d",&n,&k,&m);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	mic[1][1][1]=tbl[0];
	int ans=0;
	for (int i=1;i<n;i++) {
		mic[i+1][i][1]=max(mic[i+1][i][1],mic[i][0][0]+tbl[i]);
		if (i==n-1) {
			ans=max(ans,mic[i][0][0]+tbl[i]);
		}
		if (i-k>=1) {
			mic[i+1][0][0]=max(mic[i+1][0][0],mic[i][i-k][1]);
			if (i==n-1) {
				ans=max(ans,mic[i][i-k][1]);
			}
		}
		for (int j=max(i-k+1,1);j<i;j++) {
			for (int kk=1;kk<=k;kk++) {
				if (kk==1) {
					mic[j+k][i][1]=max(mic[j+k][i][1],mic[i][j][1]+tbl[i]);
				}
				mic[i+1][j][kk]=max(mic[i+1][j][kk],mic[i][j][kk]);
				mic[i+1][j][kk+1]=max(mic[i+1][j][kk],mic[i][j][kk]+tbl[i]);
				if (i==n-1) {
					if (kk!=k) ans=max(ans,mic[i][j][kk]+tbl[i]);
					ans=max(ans,mic[i][j][kk]);
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
