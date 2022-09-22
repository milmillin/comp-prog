#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

struct app{
	int d,s;
	int id;

	int req() const {
		return max(d,s);
	}

	int drop() const {
		return req()-s;
	}
};

bool operator< (const app &a, const app &b) {
	return a.drop()>b.drop();
}

app apps[600];

int par[600][10100];
int dp[600][10100];

int main () {
	int n,c;
	scanf("%d%d",&n,&c);
	for (int i=1;i<=n;i++) {
		scanf("%d%d",&apps[i].d,&apps[i].s);
		apps[i].id=i;
	}
	sort(apps+1,apps+n+1);
	memset(par,-1,sizeof(par));
	memset(dp,-1,sizeof(dp));
	dp[0][c]=0;
	par[0][c]=0;
	for (int i=1;i<=n;i++) {
		for (int j=0;j<=c;j++) {
			if (dp[i-1][j]==-1) continue;
			if (dp[i][j]<dp[i-1][j]) {
				dp[i][j]=dp[i-1][j];
				par[i][j]=0;
			}
			if (j<apps[i].req()) continue;
			if (dp[i][j-apps[i].s]<dp[i-1][j]+1) {
				dp[i][j-apps[i].s]=dp[i-1][j]+1;
				par[i][j-apps[i].s]=i;
			}
		}
	}
	int ans=-1;
	int mxid=-1;
	for (int i=0;i<=c;i++) {
		if (dp[n][i]>ans) {
			ans=dp[n][i];
			mxid=i;
		} 
	}
	vector<int> items;
	for (int i=n;i>=1;i--) {
		if (par[i][mxid]==0) continue;
		items.push_back(apps[par[i][mxid]].id);
		mxid+=apps[par[i][mxid]].s;
	}
	reverse(items.begin(),items.end());
	assert(ans==items.size());
	printf("%d\n",ans);
	for (auto i:items) {
		printf("%d ",i);
	}
	printf("\n");
	return 0;
}
