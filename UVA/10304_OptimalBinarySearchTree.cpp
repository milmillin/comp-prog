#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int tbl[300];
int qs[300];
int mic[300][300];

int dp(int left,int rgt) {
	if (rgt<left) return 0;
	if (mic[left][rgt]!=-1) return mic[left][rgt];
	if (left==rgt) return mic[left][rgt]=0;
	int mn=2e9;
	for (int i=left;i<rgt;i++) {
		mn=min(mn,dp(left,i)+qs[i-1]-qs[left-1]+dp(i+1,rgt)+qs[rgt-1]-qs[i]+tbl[i]);
	}
	return mic[left][rgt]=mn;
}

void f(int n) {
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		qs[i]=tbl[i]+qs[i-1];
	}
	memset(mic,-1,sizeof(mic));
	printf("%d\n",dp(1,n+1)-qs[n]);
}

int main () {
	int n;
	while (scanf("%d",&n)!=EOF) {
		f(n);
	}
	return 0;
}
