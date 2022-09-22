#include <cstdio>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

long long gcd(long long a,long long b) {
	return (b==0)?a:gcd(b,a%b);
}

int mod = 1000000007;
long long poww(int x) {
	if (x==0) return 1;
	if (x==1) return 2;
	long long tmp = poww(x/2);
	tmp*=tmp;
	tmp%=mod;
	if (x%2) return (tmp*2)%mod;
	return tmp;
}

int main () {
	freopen("gymnasts.in","r",stdin);
	freopen("gymnasts.out","w",stdout);
	long long n;
	scanf("%lld",&n);
	
	long long ans=1;
	for (int i=1;i<n;i++) {
		ans+=poww(gcd(i,n))-1;
		ans%=mod;
		//printf("%d %lld\n",i,gcd(i,n));
	}
	printf("%lld\n",ans);
	return 0;
}

int _main () {
	long long n;
	scanf("%lld",&n);
	long long sq = (long long)floor(sqrt(n));
	vector<long long> fac;
	for (int i=2;i<=sq;i++) {
		if (n%i==0) {
			fac.push_back(i);
			if (i!=sq) fac.push_back(n/i);
		}
	}
	sort(fac.begin(),fac.end());
	printf("%d\n",fac.size());
	for (auto i:fac) {
		printf("%lld\n",i);
	}
}
