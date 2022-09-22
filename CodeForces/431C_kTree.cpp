#include <cstring>
#include <cstdio>

using namespace std;

int n,k,d;

int mic[200][2];
int mod=1000000007;

int dp(int i,bool st) {
	if (i<0) return 0;
	if (i==0) {
		if (st) return 1;
		else return 0;
	}
	if (mic[i][st]!=-1) return mic[i][st];
	int ans=0;
	for (int ii=1;ii<=k;ii++) {
		ans+=dp(i-ii,st||(ii>=d));
		ans%=mod;
	}
	return mic[i][st]=ans;
}

int main () {
	scanf("%d%d%d",&n,&k,&d);
	memset(mic,-1,sizeof(mic));
	printf("%d\n",dp(n,0));
	return 0;
}
