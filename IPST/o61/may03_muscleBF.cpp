#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;


int tbl[15010];
int ans[15010];

int main () {
	int n;
	scanf("%d",&n);
	assert(n<15010);
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	for (int i=0;i<n;i++) {
		int cur=-1;
		for (int j=0;j<n;j++) {
			if (tbl[j]==j) cur=j;
		}
		for (int j=cur;j<n;j++) {
			tbl[j]++;
		}
		ans[cur]=i+1;
	}
	for (int i=0;i<n;i++) {
		printf("%d ",ans[i]);
	}
	printf("\n");
	return 0;
}
