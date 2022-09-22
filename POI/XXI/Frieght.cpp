#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

long long tbl[1000100];
long long n,s;

bool check(long long mid) {
	long long cur=mid;
	long long curi=n;
	//printf("-- %lld\n",cur);
	long long num;
	while (curi&&cur-tbl[curi]>=2*s) {
		//printf("%lld %lld\n",cur,curi);
		num=min(curi,cur-tbl[curi]-2*s+1);
		cur=tbl[curi]-num+1;
		curi-=num;
	}
	return curi==0;
}

int main () {
	scanf("%lld%lld",&n,&s);
	tbl[0]=-1;
	for (int i=1;i<=n;i++) {
		scanf("%lld",&tbl[i]);
		tbl[i]=max(tbl[i],tbl[i-1]+1);
	}	
	long long lo=tbl[n]+2*s;
	long long hi=tbl[n]+n*s;
	long long mid;
	while (lo<hi) {
		mid=(lo+hi)>>1;
		if (check(mid)) {
			hi=mid;
		} else {
			lo=mid+1;
		}
	}
	printf("%lld\n",lo);
	return 0;
}
