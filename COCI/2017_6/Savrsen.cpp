#include <cstdio>

using namespace std;

long long tbl[10000100];

int main () {
	for (int i=1;i<10000100;i++) {
		tbl[i]=i;
	}
	for (int i=1;i<10000100;i++) {
		for (int j=i+i;j<10000100;j+=i) {
			tbl[j]-=i;
		}
	}
	int a,b;
	scanf("%d%d",&a,&b);
	long long sum=0;
	for (int i=a;i<=b;i++) {
		if (tbl[i]<0) tbl[i]=-tbl[i];
		sum+=tbl[i];
	}
	printf("%lld\n",sum);
	return 0;
}
