#include <cstdio>
#include <cstring>

using namespace std;

long long mem1[50],mem2[50];

long long b(int n);

long long a(int n) {
	if (mem1[n]!=-1) return mem1[n];
	return mem1[n]=2*b(n-1)+a(n-2);
}

long long b(int n) {
	if (mem2[n]!=-1) return mem2[n];
	return mem2[n]=a(n-1)+b(n-2);
}

int main () {
	memset(mem1,-1,sizeof(mem1));
	memset(mem2,-1,sizeof(mem2));
	mem2[0]=0;
	mem1[0]=1;
	mem2[1]=1;
	mem1[1]=0;
	int n;
	while (true) {
		scanf("%d",&n);
		if (n==-1) break;
		printf("%lld\n",a(n));
	}
	return 0;
}
