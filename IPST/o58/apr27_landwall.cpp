#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int mic[1010][1010];
int tbl[1010];

int dp(int x,int k) {
	if (k<0) return -2e9;
	if (x<0) return 0;
	if (mic[x][k]!=-1) return mic[x][k];
	return mic[x][k]=max(tbl[x]+dp(x-2,k),max(tbl[x]+dp(x-1,k-1),dp(x-1,k)));
}

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	memset(mic,-1,sizeof(mic));
	printf("%d\n",dp(n-1,k));

}
