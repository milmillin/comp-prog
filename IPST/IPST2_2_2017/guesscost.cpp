#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[400];
int mic[400][400];

int recur(int l,int r) {
	if (l>r) return 0;
	if (l==r) return tbl[l];
	if (mic[l][r]!=-1)return mic[l][r];
	int ans=2e9;
	for (int i=l;i<=r;i++) {
		ans=min(ans,max(recur(l,i-1),recur(i+1,r))+tbl[i]);
	}
	return mic[l][r]=ans;
}

int main () {
	int n;
	scanf("%d",&n);

	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}

	memset(mic,-1,sizeof(mic));
	printf("%d\n",recur(1,n));
	
	return 0;
}
