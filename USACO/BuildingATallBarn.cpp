#include <cstdio>
#include <cmath>

using namespace std;

long long tbl[100100];
int n;

long long solve(double x) {
	long long cnt=0;
	for (int i=0;i<n;i++) {
		cnt+=(long long)((sqrt(1+4*tbl[i]/x)-1)/2);
	}
	return cnt;
}

int main () {
	freopen("tallbarn.in","r",stdin);
	freopen("tallbarn.out","w",stdout);
	long long k;
	scanf("%d%lld",&n,&k);
	k-=n;
	for (int i=0;i<n;i++) {
		scanf("%lld",&tbl[i]);
	}
	double lo=0,hi=1e18;
	for (int i=0;i<200;i++) {
		double mid=(lo+hi)/2;
		if (solve(mid)>=k) lo=mid;
		else hi=mid;
	}

	double ans=0;
	long long tot=0;
	
	for (int i=0;i<n;i++) {
		long long x=(long long)((sqrt(1+4*tbl[i]/lo)-1)/2);
		ans += (double)tbl[i]/(x+1);
		tot += x;
	}
	printf("%lld\n",(long long)round(ans-(k-tot)*lo));
	return 0;
}
