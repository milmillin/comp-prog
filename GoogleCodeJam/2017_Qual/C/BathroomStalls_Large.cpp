#include <cstdio>
#include <algorithm>

using namespace std;

void f() {
	long long n,k;
	scanf("%lld%lld",&n,&k);
	int lev;
	for (int i=61;i>=0;i--) {
		if ((1ll<<i)-1<=n) {
			n-=(1ll<<i)-1;
			lev=i;
			break;
		}	
	}
	if (k>=(1ll<<lev)) {
		printf("0 0\n");
		return;
	}
	long long klev;
	long long spc;

	for (int i=61;i>=0;i--) {
		if ((1ll<<i)-1<k) {
			k-=(1ll<<i)-1;
			spc=(1ll<<(lev-i))-2;
			klev=1ll<<i;
			break;
		}
	}
	
	long long lo=0;
	long long hi=n;
	long long mid=0;

	while (lo<hi) {
		mid=(lo+hi+1)>>1;
		//printf("%lld\n",mid);
		if (klev*mid+k>n) {
			hi=mid-1;
		} else {
			lo=mid;
		}
	}
	spc+=mid;

	long long spc2=spc/2;
	spc-=spc2;
	printf("%lld %lld\n",max(spc,spc2),min(spc,spc2));
	//printf("%lld %d %lld %lld %lld\n",n,lev,k,klev,spc);
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}
