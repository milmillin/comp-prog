#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[200];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	int a,b;
	for (int i=0;i<m;i++) {
		scanf("%d%d",&a,&b);
		if (tbl[a]==0) tbl[a]=b;
		else tbl[a]=min(tbl[a],b);
	}
	int sum=0;
	for (int i=1;i<=n;i++) {
		sum+=tbl[i];
	}
	printf("%d\n",sum);
	for (int i=1;i<=n;i++) {
		printf("%d %d\n",i,tbl[i]);
	}
    return 0;
}
