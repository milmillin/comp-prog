#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int dp[60][60][2][2][3010];
int tbl[60][3010];
int n,m;
int di[9][2]={{-1,-1},{0,-1},{1,-1},{-1,0},{0,0},{1,0},{-1,1},{0,1},{1,1}};

int mic(int i,int j,int si,int sj, int k) {
	if (i<0||i>=n||j<0||j>=n) return -2e9;
	if (si<0||sj<0) return -2e9;
	//if (k==-1) return 0;
	//printf("++%d %d %d %d %d\n",i,j,si,sj,k);
	if (dp[i][j][si][sj][k]!=-1) return dp[i][j][si][sj][k];
	int ans=0;
	if (k) {
		for (int ii=0;ii<9;ii++) {
			ans=max(ans,mic(i+di[ii][0],j+di[ii][1],((i+di[ii][0]==i)?si-1:1),((j+di[ii][1]==j)?sj-1:1),k-1));
		}
	}
	ans+=tbl[i][k];
	if (i!=j) ans+=tbl[j][k];
//printf("--%d %d %d %d %d %d\n",i,j,si,sj,k,ans);
	return dp[i][j][si][sj][k]=ans;
}

int main () {
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		for (int j=0;j<m;j++) {
			scanf("%d",&tbl[i][m-j-1]);
		}
	}
	memset(dp,-1,sizeof(dp));
	int ans=mic(0,n-1,1,1,m-1);
	printf("%d\n",ans);
	return 0;
}
