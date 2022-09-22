#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[100100];

int main () {
	int n;
	scanf("%d",&n);
	int sum=0;
	int x;
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		sum+=tbl[i];
		tbl[i]+=tbl[i-1];
	}
	if (sum%2) {
		printf("NO\n");
		return 0;
	}
	sum/=2;
	for (int i=0;i<n;i++) {
		int* loc = lower_bound(tbl+i,tbl+n+1,sum+tbl[i]);
		if (*loc==sum+tbl[i]) {
			if (i) printf("%d ",i);
			printf("%d\n",loc-tbl);
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
