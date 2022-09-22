#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>

using namespace std;

int mic[200][10010];
int tbl[200];
int par[200][10010];

int dp(int i,int j) {
	if (tbl[i]>j) return 0;
	if (mic[i][j]!=-1) return mic[i][j];
	//printf("-- %d %d\n",i,j);
	int ans=1;
	par[i][j]=-1;
	for (int ii=0;ii<i;ii++) {
		//ans=max(ans,1+dp(ii,min(tbl[i]*6,j-tbl[i])));
		int tmp=1+dp(ii,min(tbl[i]*6,j-tbl[i]));
		if (tmp>ans) {
			ans=tmp;
			par[i][j]=ii;
		}
	}
	int tmp=dp(i,j-1);
	if (tmp>ans) {
		ans=tmp;
		par[i][j]=par[i][j-1];
	}
	return mic[i][j]=ans;
	//return mic[i][j]=max(ans,dp(i,j-1));
}

void f() {
	int n;
	scanf("%d",&n);
	assert(n<=100);
	memset(mic,-1,sizeof(mic));
	memset(tbl,0,sizeof(tbl));
	memset(par,-1,sizeof(par));
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	int ans=0;
	int cur=-1;
	for (int i=0;i<n;i++) {
		//printf("%d\n",i);
		for (int j=0;j<10001;j++) {
			dp(i,j);
		}
		int tmp=dp(i,10000);
		//ans=max(ans,dp(i,10000));
		if (tmp>ans) {
			ans=tmp;
			cur=i;
		}
	}
	printf("%d %d\n",cur,par[cur][10000]);
	printf("%d\n",ans);
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}
