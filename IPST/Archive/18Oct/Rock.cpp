#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[100];
int mem[100][100][2];

int recur(int l,int r,int st) {
	//printf("%d %d %d\n",l,r,st);
	if (mem[l][r][st]!=-1) return mem[l][r][st];
	if (!st) {
		//my turn
		if (l==r) return tbl[l];
		return mem[l][r][st]=max(tbl[l]+recur(l+1,r,!st),tbl[r]+recur(l,r-1,!st));
	} else {
		//opponent's turn
		if (l==r) return 0;
		return mem[l][r][st]=max(recur(l+1,r,!st),recur(l,r-1,!st));
	}
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n*2;i++) {
		scanf("%d",&tbl[i]);
	}
	memset(mem,-1,sizeof(mem));
	printf("%d\n",recur(0,2*n-1,0));
	return 0;
}
