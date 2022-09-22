#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int a[200];
int b[200];

int sz[200];
int getSz(int l,int r) {
	if (sz[l]!=-1) return sz[l];
	int cur=0;
	while (b[r+cur++]!=a[l]);
	return sz[l]=cur;
}

int mod=1000000007;

long long mic[200][200][200];
long long dp(int l,int r,int n) {
	if (n==0||n==1) return 1;
	if (mic[l][r][n]!=-1) return mic[l][r][n];
	int aa=getSz(l,r);
	long long left=dp(l+1,r,aa-1);
	long long rgt=0;
	int ss=n-aa;
	for (int i=0;i<=ss;) {
		rgt+=(dp(l+aa,r+aa,i)*dp(l+aa+i,r+aa+i,ss-i))%mod;
		rgt%=mod;
		if (i==ss) break;
		i+=getSz(l+aa+i,r+aa+i);
	}
	rgt*=left;
	rgt%=mod;
	return mic[l][r][n]=rgt;
}


int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&a[i]);
	}
	for (int i=0;i<n;i++) {
		scanf("%d",&b[i]);
	}
	memset(sz,-1,sizeof(sz));
	memset(mic,-1,sizeof(mic));
	printf("%lld\n",dp(0,0,n));
	return 0;
}
