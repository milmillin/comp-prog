#include <cstdio>
#include <algorithm>

using namespace std;

long long tbl[1000100];

int main () {
	int n,s;
	scanf("%d%d",&n,&s);
	long long cnt=0;
	for (int i=0;i<n;i++) {
		scanf("%lld",&tbl[i]);
		if (i) {
			tbl[i]=max(tbl[i],tbl[i-1]+1);
		}
	}	
	for (int i=n-1;i>0;i--) {
		if (tbl[i]-tbl[i-1]<2*s) {
			tbl[i-1]=tbl[i]-1;
		}
	}
	for (int i=0;i<n;i++) {
		if (i) {
			cnt-=min(cnt,max(0ll,tbl[i]-tbl[i-1]-s+1-s));
		}
		cnt++;
	}
	tbl[n-1]+=s;
	tbl[n-1]+=s+cnt-1;
	printf("%lld\n",tbl[n-1]);
	return 0;
}
