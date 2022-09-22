#include <cstdio>
#include <algorithm>

using namespace std;

long long f (long long x) {
	if (x==1) return 0;
	if (x&1) {
		return f(x/2);
	}
	return x/2;
}

int mex(long long a,long long b) {
	if (a!=0&&b!=0) return 0;
	if (a!=1&&b!=1) return 1;
	return 2;
}

int main () {
	int q;
	scanf("%d",&q);
	int n;
	long long x;
	while (q--) {
		scanf("%d",&n);
		int ans=0;
		for (int i=0;i<n;i++) {
			scanf("%lld",&x);
			ans^=mex(f(x),f(x-1));
		}
		printf("%d\n",(ans)?1:0);
	}
	return 0;
}
