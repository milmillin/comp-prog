#include <cstdio>
#include <algorithm>

using namespace std;


long long tbl[10000100];

int main () {
	int n,x,y;
	scanf("%d%d%d",&n,&x,&y);
	tbl[0]=0;
	tbl[1]=x;
	for (int i=2;i<=n;i++) {
		if (i%2==0) {
			tbl[i]=min(tbl[i/2]+y,tbl[i-1]+x);
		} else {
			tbl[i]=min(tbl[i-1]+x,tbl[(i+1)/2]+x+y);
		}
	}
	printf("%I64d\n",tbl[n]);
	return 0;
}
