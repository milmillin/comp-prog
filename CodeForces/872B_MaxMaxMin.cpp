#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[100100];
int ml[100100];
//int mr[100100];

int main() {
	int n,k;
	scanf("%d%d",&n,&k);
	int mn=2e9;
	int mx=-2e9;
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		mn=min(mn,tbl[i]);
		ml[i]=mn;
		mx=max(mx,tbl[i]);
	}
	if (k==1) {
		printf("%d\n",mn);
		return 0;
	}
	if (k>=3) {
		printf("%d\n",mx);
		return 0;
	}
	mn=2e9;
	int ans=-2e9;
	for (int i=n-1;i>=0;i--) {
		mn=min(mn,tbl[i]);
		if (i) {
			ans=max(ans,max(ml[i-1],mn));
		}
	}
	if (k==2) {
		printf("%d\n",ans);
		return 0;
	}

	return 0;
}
