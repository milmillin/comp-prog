#include <cstdio>

using namespace std;

int main () {
	int n;
	scanf("%d",&n);
	for (long long i=1;i<=3500;i++) {
		for (long long j=1;j<=3500;j++) {
			//printf("%lld\n",4*i*j-n*(i+j));
			if (4*i*j-n*(i+j)==0) continue;
			if ((n*i*j)%(4*i*j-n*(i+j))==0) {
				long long ans=(n*i*j)/(4*i*j-n*(i+j));
				if (ans<=0) continue;
				printf("%lld %lld %lld\n",i,j,ans);
				return 0;
			}
		}
	}
	return 0;
}
