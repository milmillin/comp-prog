#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

int tbl[100];
int cost[100][100];
int b[100];

long long dp[100][100][100];

struct ei {
	int id;
	long long c;
};

bool operator< (const ei &a, const ei &b) {
	return a.c>b.c;
}

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		tbl[i]--;
	}
	for (int i=0;i<m;i++) {
		for (int j=0;j<m;j++) {
			scanf("%d",&cost[i][j]);
		}
	}
	for (int i=0;i<m;i++) {
		scanf("%d",&b[i]);
	}

	for (int k=0;k<m;k++) {
		for (int i=0;i<m;i++) {
			for (int j=0;j<m;j++) {
				cost[i][j]=min(cost[i][j],cost[i][k]+cost[k][j]);
			}
		}
	}

	priority_queue<ei> q;

	for (int i=0;i<n;i++) {
		for (int k=0;k<m;k++) {
			if (tbl[i]==k) dp[i][i][k]=0;
			else dp[i][i][k]=cost[tbl[i]][k];
		}
	}	

	for (int sz=2;sz<=n;sz++) {
		for (int i=0;i+sz-1<n;i++) {
			int j=i+sz-1;
			for (int k=0;k<m;k++) {
				dp[i][j][k]=1e18;
				for (int x=i;x<j;x++) {
					dp[i][j][k]=min(dp[i][j][k],dp[i][x][(k-1+m)%m]+dp[x+1][j][(k-1+m)%m]+b[(k-1+m)%m]);
				}
				q.push(ei{k,dp[i][j][k]});
			}
			while (!q.empty()) {
				auto x=q.top();
				q.pop();
				if (dp[i][j][x.id]<x.c) continue;
				for (int k=0;k<m;k++) {
					if (dp[i][j][k]<=dp[i][j][x.id]+cost[x.id][k]) continue;
					dp[i][j][k]=dp[i][j][x.id]+cost[x.id][k];
					q.push(ei{k,dp[i][j][k]});
				}
			}
			//for (int k=0;k<m;k++) {
				//printf("%d,",dp[i][j][k]);
			//}
			//printf(" ");
		}
		//printf("\n");
	}

	long long ans=1e18;
	for (int i=0;i<m;i++) {
		ans=min(ans,dp[0][n-1][i]);
	}
	printf("%lld\n",ans);
	return 0;
}
