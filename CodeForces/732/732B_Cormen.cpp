#include <cstdio>

using namespace std;

int tbl[1000];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	int ans=0;
	for (int i=1;i<n;i++) {
		if (tbl[i]+tbl[i-1]<k) {
			ans+=k-tbl[i-1]-tbl[i];
			tbl[i]=k-tbl[i-1];
		}
	}
	printf("%d\n",ans);
	for (int i=0;i<n;i++) {
		printf("%d ",tbl[i]);
	}
	printf("\n");
	return 0;
}
