#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[100][100];
int mem[60][60][60][60];

int solve(int r1,int c1,int r2,int c2) {
	if (mem[r1][c1][r2][c2]!=-1) return mem[r1][c1][r2][c2];
	if (r1==r2&&c1==c2) {
		return 0;
	}
	int mn=0x3f3f3f3f;
	for (int i=r1;i<r2;i++) {
		mn=min(mn,solve(r1,c1,i,c2)+solve(i+1,c1,r2,c2));
	}
	for (int i=c1;i<c2;i++) {
		mn=min(mn,solve(r1,c1,r2,i)+solve(r1,i+1,r2,c2));
	}
	return mem[r1][c1][r2][c2]=mn+tbl[r2][c2]-tbl[r1-1][c2]-tbl[r2][c1-1]+tbl[r1-1][c1-1];
}

int main () {
	int r,c;
	scanf("%d%d",&r,&c);
	for (int i=1;i<=r;i++) {
		for (int j=1;j<=c;j++) {
			scanf("%d",&tbl[i][j]);
			tbl[i][j]+=tbl[i-1][j]+tbl[i][j-1]-tbl[i-1][j-1];
		}
	}
	memset(mem,-1,sizeof(mem));
	printf("%d\n",solve(1,1,r,c));
	return 0;
}
