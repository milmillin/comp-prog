#include <cstdio>
#include <algorithm>

using namespace std;


long long val[200][200];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			val[i][j]=1;
			for (int k=1;k<i;k++) {
				for (int l=1;l<j;l++) {
					val[i][j]+=val[k][l];
				}
			}
			printf("%lld ",val[i][j]);
		}
		printf("\n");
	}
	return 0;
}
