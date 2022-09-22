#include <cstdio>
#include <algorithm>

using namespace std;

int cnt3[200][200];
int cnt2[200][200];

int dp[200][200][2000];

int main () {
	int r,c;
	scanf("%d%d",&r,&c);
	int x;
	for (int i=0;i<=r;i++) {
		for (int j=0;j<=c;j++) {
			for (int k=0;k<2000;k++) dp[i][j][k]=-1e9;
		}
	}
	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++) {
			scanf("%d",&x);
			while (x%2==0) {
				cnt2[i][j]++;
				x/=2;
			}
			while (x%3==0) {
				cnt3[i][j]++;
				x/=3;
			}
			dp[i][j][cnt3[i][j]]=cnt2[i][j];
		}
	}

	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++) {
			for (int k=0;k<2000;k++) {
				dp[i+1][j][k+cnt3[i+1][j]]=max(dp[i+1][j][k+cnt3[i+1][j]],dp[i][j][k]+cnt2[i+1][j]);
				dp[i][j+1][k+cnt3[i][j+1]]=max(dp[i][j+1][k+cnt3[i][j+1]],dp[i][j][k]+cnt2[i][j+1]);
			}
		}
	}

	int ans=0;
	for (int i=0;i<2000;i++) {
		ans=max(ans,min(i,dp[r][c][i]));
	}
	printf("%d\n",ans);
	return 0;
}
