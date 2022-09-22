#include <cstdio>
#include <cstring>

using namespace std;

int tbl[80100];

int bit[50][80100];
int dp[50][80100];

int mod=1e9-1;

int get(int *bb,int idx) {
	int sum=0;
	while (idx) {
		sum+=bb[idx];
		sum%=mod;
		idx-=(idx&-idx);
	}	
	return sum;
}

void add(int *bb,int idx,int val) {
	while (idx<80100) {
		bb[idx]+=val;
		bb[idx]%=mod;
		idx+=(idx&-idx);
	}
}

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		dp[0][i]=1;
	}
	int ans=0;
	for (int i=1;i<k;i++) {
		for (int j=0;j<n;j++) {
			dp[i][j]=get(bit[i-1],n)-get(bit[i-1],tbl[j]);
			dp[i][j]%=mod;
			dp[i][j]+=mod;
			dp[i][j]%=mod;
			add(bit[i-1],tbl[j],dp[i-1][j]);
		}
	}
	for (int i=0;i<n;i++) {
		ans+=dp[k-1][i];
		ans%=mod;
	}
	printf("%d\n",ans);
	return 0;
}
