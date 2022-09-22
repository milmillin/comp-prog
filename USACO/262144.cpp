#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

int dp[60][300000];

int main () {
	freopen("262144.in","r",stdin);
	freopen("262144.out","w",stdout);
	int n;
	scanf("%d",&n);
	vector<int> tbl(n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}

	int ans=1;
	for (int i=1;i<60;i++) {
		for (int j=0;j<n;j++) {
			if (tbl[j]==i) {
				dp[i][j]=j+1;
			} else {
				if (i==1) dp[i][j]=-1;
				else {
					if (dp[i-1][j]==-1) dp[i][j]=-1;
					else{
						dp[i][j]=dp[i-1][dp[i-1][j]];
					}
				}
			}
			if (dp[i][j]!=-1) ans=max(ans,i);
		}
		dp[i][n]=-1;
	}
	printf("%d\n",ans);
	return 0;
}
