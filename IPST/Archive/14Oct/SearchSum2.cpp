#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[1100];
int minn[1100];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		tbl[i]+=tbl[i-1];
		minn[i]=2e9;
	}
	for (int i=1;i<=n;i++) {
		for (int j=i;j<=n;j++) {
			minn[j-i+1]=min(minn[j-i+1],tbl[j]-tbl[i-1]);
		}
	}

	int x;
	for (int i=0;i<k;i++) {
		scanf("%d",&x);
		printf("%d\n",upper_bound(minn,minn+1+n,x)-minn-1);
	}
	return 0;
}
