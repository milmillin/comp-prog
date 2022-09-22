#include <cstdio>

using namespace std;

long long aa;

long long f(long long a,long long b) {
	if (a==0) return -b;
	return 2*a*(b/a)+f(b%a,a);
}


int main () {
	long long n,x;
	scanf("%lld%lld",&n,&x);
	printf("%lld\n",n+f(x,n-x));
	return 0;
}
