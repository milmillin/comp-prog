#include <cstdio>

using namespace std;

int tbl[200];

int main () {
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1;i<=n;i++) {
		scanf("%d",&tbl[i]);
	}
	for (int i=1;i<n;i++) {
		//printf("%d %d\n",m-i,m+i);
		if (m-i>0&&tbl[m-i]&&tbl[m-i]<=k) {
			printf("%d\n",i*10);
			return 0;
		}
		if (m+i<=n&&tbl[m+i]&&tbl[m+i]<=k) {
			printf("%d\n",i*10);
			return 0;
		}
	}
	return 0;
}
