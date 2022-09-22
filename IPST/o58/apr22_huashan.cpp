#include <cstdio>

using namespace std;

int main () {
	int n,b,e;
	scanf("%d%d%d",&n,&b,&e);
	n--;
	long long cnt=0;
	while (n>1) {
		cnt++;
		n/=2;
	}
	cnt*=b+e;
	cnt-=b;
	printf("%lld\n",cnt);
	return 0;
}
