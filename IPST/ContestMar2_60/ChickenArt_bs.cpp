#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>

using namespace std;

int tbl[1010];
long long qs1[1010];


int dp1[1010][1010];
int dp2[1010][1010];

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	assert(n<1010);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		qs1[i]=qs1[i-1]+tbl[i];
	}
	//for (int i=n;i>=1;i--) {
		//qs2[i]=qs2[i+1]+tbl[i];
	//}
	memset(dp1,63,sizeof(dp1));
	memset(dp2,63,sizeof(dp2));
	
	for (int i=1;i<=m;i++) {
		dp1[1][i]=qs1[i];
		//printf("%d ",dp1[1][i]);
	}
	//printf("\n");
	for (int i=2;i<=k;i++) {
		for (int j=i;j<=n;j++) {
			for (int kk=1;kk<=m;kk++) {
				if (j-kk<=0) break;
				dp1[i][j]=min(dp1[i][j],max(dp1[i-1][j-kk],(int)(qs1[j]-qs1[j-kk])));
			}
			//printf("%d ",dp1[i][j]);
		}
		//printf("\n");
	}
	//printf("---\n");
	for (int i=n;i>=n-m+1;i--) {
		dp2[1][i]=qs1[n]-qs1[i-1];
		//printf("yay\n");
		//printf("%d ",dp2[1][i]);
	}
	//printf("\n");
	for (int i=2;i<=k;i++) {
		for (int j=n-i+1;j>=1;j--) {
			for (int kk=1;kk<=m;kk++) {
				if (j+kk>n) break;
				dp2[i][j]=min(dp2[i][j],max(dp2[i-1][j+kk],(int)(qs1[j+kk-1]-qs1[j-1])));
			}
			//printf("%d ",dp2[i][j]);
		}
		//printf("\n");
	}
	
	int mypart=min(n-k+1,m);
	int cur=0;
	int ans=min(dp1[k-1][n-mypart],dp2[k-1][mypart+1]);
	int tmp;
	for (int i=2;i<=n;i++) {
		if (i+mypart-1>=n) break;
		int curr=max(dp1[cur][i-1],dp2[k-cur-1][i+mypart]);		
		while ((tmp=max(dp1[cur+1][i-1],dp2[k-cur-2][i+mypart]))<curr) {
			curr=tmp;
			cur++;			
		}
		//printf("%d %d %d\n",curr,tmp,cur);
		ans=min(ans,curr);	
	}
	printf("%d\n",ans);
							
	return 0;
}
