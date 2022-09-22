#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int a[4010];
int b[4010];

long long mic[4010][4010];
int n;
long long c;

long long dp(int x,int y) {
	if (x==-1&&y==0) return 0;
	if (x<0||y<0) return 2e9;
	if (mic[x][y]!=-1) return mic[x][y];
	return mic[x][y]=min(dp(x-1,y)+a[x]+c*y,dp(x-1,y-1)+b[x]);
}


int main () {
	scanf("%d%lld",&n,&c);
	for (int i=0;i<n;i++) {
		scanf("%d",&a[i]);
	}
	for (int i=0;i<n;i++) {
		scanf("%d",&b[i]);
	}
	memset(mic,-1,sizeof(mic));
	//for (int i=0;i<n;i++) {
		//printf("%lld %lld\n",dp(i,0),dp(i,1));
	//}
	long long ans=1e18;
	for (int i=0;i<=n;i++) {
		ans=min(ans,dp(n-1,i));
	}
	printf("%lld\n",ans);
	return 0;
}
