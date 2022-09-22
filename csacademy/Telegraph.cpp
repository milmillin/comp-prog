#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long dp[2][760][760];
int dx[760];

int main () {
	for (int i=0;i<760;i++) {
		dx[i]=i&1;
	}
    int n;
    scanf("%d",&n);
    vector<int> tbl(n);
    for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
    }
    sort(tbl.begin(),tbl.end());
    reverse(tbl.begin(),tbl.end());
    vector<int> sum(n+1);
    sum[n]=0;
    for (int i=n-1;i>=0;i--) {
        sum[i]=sum[i+1]+tbl[i];
    }

    for (int i=0;i<=n;i++) {
        for (int j=0;j<=n;j++) {
			dp[0][i][j]=1e17;
        }
    }
    dp[0][1][1]=sum[0];
    for (int s=0;s<n;s++) {
        for (int i=0;i<=n;i++) {
            for (int j=0;j<=n;j++) {
				dp[dx[s+1]][i][j]=1e17;
                int ni=min(n,i+j);
                int nj=min(n,i);
				dp[dx[s]][ni][nj]=min(dp[dx[s]][ni][nj],dp[dx[s]][i][j]+sum[s]);
            }
        }
        
        for (int i=1;s+i<=n;i++) {
            for (int j=0;s+i+j<=n;j++) {
				dp[dx[s+1]][i-1][j]=min(dp[dx[s+1]][i-1][j],dp[dx[s]][i][j]);
            }
        }
    }
    long long ans=1e17;
	
    for (int i=0;i<=n;i++) {
        for (int j=0;j<=n;j++) {
            ans=min(ans,dp[dx[n]][i][j]);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
