#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int fact[100100];
int mod=10007;
int ifact[100100];

int poww(int x,int b) {
	if (b==0) return 1;
	if (b==1) return x;
	int tmp=poww(x,b/2);
	tmp*=tmp;
	tmp%=mod;
	if (b%2) return (tmp*x)%mod;
	return tmp;
}

void init() {
	fact[0]=1;
	ifact[0]=poww(fact[0],mod-2);
	for (int i=1;i<100100;i++) {
		fact[i]=fact[i-1]*i;
		fact[i]%=mod;
		ifact[i]=poww(fact[i],mod-2);
	}
}

int dp[100100];

int main () {
	init();
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	assert(n<=2*k);
	dp[2]=1;
	for (int i=4;i<=n;i+=2) {
		dp[i]=i*(i-1)/2*dp[i-2];
		dp[i]/=2;
		dp[i]%=mod;
	}
	printf("%d\n",dp[n]);
	return 0;
}
