#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[500100];
int n,b;

bool work(int mid) {
	int cnt=0;
	for (int i=0;i<n;i++) {
		cnt+=ceil((double)tbl[i]/mid);
	}
	//printf("%d %d\n",mid,cnt);
	if (cnt<=b) return true;
	return false;
}

int main () {
	scanf("%d%d",&n,&b);
	int lo=1;
	int hi=0;
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		hi=max(hi,tbl[i]);
	}
	int mid;
	while (lo<hi) {
		mid=(lo+hi)/2;
		if (work(mid)) hi=mid;
		else lo=mid+1;
	}
	printf("%d\n",hi);
	return 0;
}
