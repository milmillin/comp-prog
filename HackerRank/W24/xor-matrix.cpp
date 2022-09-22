#include <cstdio>

using namespace std;

int tbl[2][100100];

int main () {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[0][i]);
	}
	for (int i=1;i<m;i++) {
		for (int j=0;j<n;j++) {
			tbl[i%2][j]=tbl[(i+1)%2][j]^tbl[(i+1)%2][(j+1)%n];
			printf("%d ",tbl[i%2][j]);
		}
		printf("\n");
	}
	return 0;
}
