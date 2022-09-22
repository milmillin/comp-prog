#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

int tbl[600][600];

int main () {
	int m,n,k;
	scanf("%d%d%d",&m,&n,&k);
	assert(k==0);
	int t=max(m,n);
	printf("%d\n",t);
	int s=min(m,n);
	for (int i=0;i<t;i++) {
		printf("%d ",s);	
		for (int j=0;j<n;j++) {
			int tmp=(j+i)%t+1;
			if (tmp>m) continue;
			printf("%d %d ",tmp,j+1);
		}
		printf("\n");
	}
	return 0;
}
