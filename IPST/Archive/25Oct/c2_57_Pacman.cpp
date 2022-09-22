#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[1010][1010];

int mem[1010][1010][3];

int recur(int r,int c,int st) {
	if (r==0&&c==0){
		if (st==1) return tbl[0][0];
		return 0;
	}
	if (r<0||c<0) return -2e9;
	if (mem[r][c][st]!=-1) return mem[r][c][st];
	if (st==0) {
		return mem[r][c][st]=max(max(recur(r-1,c,0),max(recur(r-1,c,1),recur(r-1,c,2))),max(recur(r,c-1,0),max(recur(r,c-1,1),recur(r,c-1,2))));
	} else if (st==1) {
		return mem[r][c][st]=max(recur(r-1,c,0),recur(r,c-1,0))+tbl[r][c];
	} else if (st==2) {
		return mem[r][c][st]=max(recur(r-1,c,1),recur(r,c-1,1))+tbl[r][c];
	}
}

int main() {
	int r,c;
	scanf("%d%d",&r,&c);
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			scanf("%d",&tbl[i][j]);
		}
	}
	memset(mem,-1,sizeof(mem));
	printf("%d\n",max(recur(r-1,c-1,0),max(recur(r-1,c-1,1),recur(r-1,c-1,2))));
	return 0;
}
