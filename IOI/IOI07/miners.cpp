#include <cstdio>
#include <algorithm>

using namespace std;

typedef unsigned char int8;

int8 mask=0x0f;

int8 ma(int8 x) {
	return x>>4;
}

int8 mb(int8 x) {
	return x&mask;
}

int8 comb(int8 a,int8 b) {
	a&=mask;
	b&=mask;
	return (a<<4)^b;
}

int8 cnt(int8 x) {
	bool mrk[4]={0,0,0,0};
	while (x) {
		mrk[x&3]=true;
		x>>=2;
	}
	return mrk[1]+mrk[2]+mrk[3];
}

int8 append(int8 x,int8 y) {
	return (x<<2)^y;	
}

int dp[100100][256];
int mp[256];

int main () {
	mp['M']=1;
	mp['B']=2;
	mp['F']=3;
	int n;
	scanf("%d",&n);
	char x;
	
	for (int i=0;i<100100;i++) {
		for (int j=0;j<256;j++) {
			dp[i][j]=0xc0000000;
		}
	}
	dp[0][0]=0;

	int8 newa,newb;
	for (int i=1;i<=n;i++) {
		scanf(" %c",&x);
		for (int j=0;j<256;j++) {
			//add a
			newa=comb(append(ma(j),mp[x]),mb(j));
			dp[i][newa]=max(dp[i][newa],dp[i-1][j]+cnt(append(ma(j),mp[x])));
			//add b
			newb=comb(ma(j),append(mb(j),mp[x]));
			dp[i][newb]=max(dp[i][newb],dp[i-1][j]+cnt(append(mb(j),mp[x])));
		}
	}		
	int ans=0;
	for (int i=0;i<256;i++) {
		ans=max(ans,dp[n][i]);
	}
	printf("%d\n",ans);
	return 0;
}
