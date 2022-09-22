#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[100100];

int main () {
	int n,k;
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
		tbl[i]+=tbl[i-1];
	}
	int x;
	for (int i=0;i<k;i++) {
		scanf("%d",&x);
		printf("%d\n",upper_bound(tbl+1,tbl+1+n,x)-tbl-1);
	}
	return 0;
}
