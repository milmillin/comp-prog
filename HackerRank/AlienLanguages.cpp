#include <cstdio>
#include <cstring>

using namespace std;

int dp[20][500100];
int mic[500100];

int md=100000007;

void f() {
	int n,m;
	scanf("%d%d",&n,&m);
	memset(dp,0,sizeof(dp));
	memset(mic,0,sizeof(mic));
	for (int i=1;i<=n;i++) {
		if (i<=n/2) {
			dp[1][i]=n-n/2;
		} else {
			dp[1][i]=n-i+1;
		}
	}
	for (int i=2;i<20;i++) {
		for (int j=1;j<=n/2;j++) {
			dp[i][j]=dp[i-1][j*2];
		}
		int cur=0;
		for (int j=n/2;j>=1;j--) {
			cur+=dp[i][j];
			cur%=md;
			dp[i][j]=cur;
		}
	}
	mic[0]=1;
	for (int i=1;i<=m;i++) {
		for (int j=1;j<20&&i>=j;j++) {
			mic[i]+=((long long)dp[j][1]*mic[i-j])%md;
			mic[i]%=md;
		}
	}
	printf("%d\n",mic[m]);
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
