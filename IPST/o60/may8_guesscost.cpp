#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[400];
int mic[400][400];

int dp(int l,int r) {
	if (l>r) return 0;
	if (l==r) return tbl[l];
	if (mic[l][r]!=-1) return mic[l][r];
	int mn=2e9;
	for (int i=l;i<=r;i++) {
		mn=min(mn,max(dp(l,i-1),dp(i+1,r))+tbl[i]);
	}
	return mic[l][r]=mn;
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	memset(mic,-1,sizeof(mic));
	printf("%d\n",dp(0,n-1));
	return 0;
}
