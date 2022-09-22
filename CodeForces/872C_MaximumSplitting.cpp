#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

bool isPrime[40000];

void init() {
	isPrime[1]=true;
	isPrime[2]=true;
	for (int i=3;i<40000;i+=2) isPrime[i]=true;
	for (int i=3;i<40000;i+=2) {
		if (!isPrime[i]) continue;
		for (int j=i*i;j<40000;j+=i) isPrime[j]=false;
	}
}

void f(int n) {
	int sq=(int)sqrt(n);
	sq++;
	int mx=-1;
	for (int i=1;i<=sq;i++) {
		if (n%i) continue;
		if (!isPrime[n/i]) mx=max(mx,i);
		if (isPrime[i]) continue;
		//printf("--\n");
		printf("%d\n",i);
		return;
	}
	printf("%d\n",n/mx);
}

int main () {
	init();
	for (int i=1;i<=100;i++) {
		printf("%d: ",i);
		f(i);
	}
	int q;
	scanf("%d",&q);
	while (q--) {
		int n;
		scanf("%d",&n);
		//f();
	}
	return 0;
}
