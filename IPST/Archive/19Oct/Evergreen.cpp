#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long tbl[1010];
int n;
long long k;

bool work(long long mid) {
	long long sum=mid*mid*n;
	long long dif;
	for (int i=1;i<n;i++) {
		dif=tbl[i-1]-tbl[i]+2*mid-1;
		if (dif<=0) continue;
		if (dif%2) {
			sum-=(dif+1)*(dif+1)/4;
		} else {
			sum-=(dif/2)*(dif/2+1);
		}
	}
	if (sum>=k) return true;
	return false;
}

int main () {
	scanf("%d%lld",&n,&k);
	for (int i=0;i<n;i++) {
		scanf("%lld",&tbl[i]);
	}
	sort(tbl,tbl+n);
	int lo=1,hi=400000000;
	int mid;
	while (lo<hi) {
		mid=(lo+hi)/2;
		if (work(mid)) hi=mid;
		else lo=mid+1;
	}
	printf("%d\n",hi-1);
	return 0;
}
