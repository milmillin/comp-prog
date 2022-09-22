#include <cstdio>
#include <cmath>

using namespace std;

int main () {
	long long sum=1;
	long long x=0;
	int cnt=0;
	while (x<1e9) {
		x=ceil((double)sum/6);
		printf("%lld %lld\n",sum,x);
		sum+=x;
		cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}
