#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;


long long mic[200][200];
int n,k;
long long mod=1e9+7;

long long dp (int a,int b) {
	if (a<0||b<0) return 0;
	if (a==0&&b==0) return 1;
	if (mic[a][b]!=-1) return mic[a][b];
	long long sum=0;
	for (int i=1;i<=k;i++) {
		sum+=dp(a-1,b-1-i);
		sum%=mod;
		sum+=dp(a-1-i,b-1);
		sum%=mod;
	}
	sum+=dp(a-1,b);
	sum%=mod;
	sum+=dp(a,b-1);
	sum%=mod;
	sum-=dp(a-1,b-1);
	sum%=mod;
	sum+=mod;
	sum%=mod;
	return mic[a][b]=sum;
}

int main () {	
	scanf("%d%d",&n,&k);
	memset(mic,-1,sizeof(mic));
	printf("%lld\n",(dp(n,n)+mod-1)%mod);
	return 0;
}
