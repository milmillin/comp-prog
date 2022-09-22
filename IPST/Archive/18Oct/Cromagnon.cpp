#include <cstdio>

using namespace std;

int res[30][30];
int tbl[200];
int cnt[200][200][30];

int main () {
	int m;
	scanf("%d",&m);
	for (int i=0;i<m;i++) {
		for (int j=0;j<m;j++) {
			scanf("%d",&res[i][j]);
		}
	}
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	for (int i=0;i<n;i++) {
		cnt[i][i][tbl[i]]++;
	}
	int j;
	int *left, *right, *now;
	for (int sz=2;sz<=n;sz++) {
		for (int i=0;i<n-sz+1;i++) {
			j=i+sz-1;
			now=cnt[i][j];
			for (int k=i;k<j;k++) {
				left=cnt[i][k];
				right=cnt[k+1][j];
				for (int a=0;a<m;a++) {
					for (int b=0;b<m;b++) {
						now[res[a][b]]+=left[a]*right[b];
						now[res[a][b]]%=2009;
					}
				}
			}
		}
	}
	for (int i=0;i<m;i++) {
		printf("%d\n",cnt[0][n-1][i]);
	}
	return 0;
}
