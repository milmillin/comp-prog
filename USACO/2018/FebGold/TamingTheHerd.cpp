#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[200];
int dp[200][200][200];

int main () {
	freopen("taming.in","r",stdin);
	freopen("taming.out","w",stdout);
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	memset(dp,63,sizeof(dp));
	dp[0][1][0]=(tbl[0]!=0);
	for (int i=1;i<n;i++) {
		for (int num=1;num<=n;num++) {
			for (int last=0;last<i;last++) {
				dp[i][num][last]=dp[i-1][num][last]+(tbl[i]!=(i-last));
			}
			for (int k=0;k<i;k++) {
				dp[i][num][i]=min(dp[i][num][i],dp[i-1][num-1][k]);
			}
			dp[i][num][i]+=(tbl[i]!=0);
		}
	}
	for (int i=1;i<=n;i++) {
		int ans=2e9;
		for (int k=0;k<n;k++) {
			ans=min(ans,dp[n-1][i][k]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
