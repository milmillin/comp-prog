#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int tbl[60];
int mem[60][60][60][60];

int lis(int l,int r,int low,int high) {
	if (mem[l][r][low][high]!=-1) return mem[l][r][low][high];
}

int main () {
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	memset(mem,-1,sizeof(mem));

	return 0;
}
