#include <cstdio>

using namespace std;

int ncr[10][10];
int ans[600];

void init() {
	ncr[0][0]=1;
	ncr[1][0]=1;
	ncr[1][1]=1;
	for (int i=2;i<10;i++) {
		ncr[i][0]=1;
		for (int j=1;j<=i;j++) {
			ncr[i][j]=ncr[i-1][j]+ncr[i-1][j-1];
		}
	}
}

int f(int x) {
	int dig=1;
	x--;
	//int sum=0;
	while (x-ncr[9][dig]>=0) {
		x-=ncr[9][dig];
		dig++;
	}
	int now=8;
	int aa=0;
	while (dig--) {
		while (x-ncr[now][dig]>=0) {
			x-=ncr[now][dig];
			now--;
		}
		aa*=10;
		aa+=9-now;
		now--;
	}
	return aa;
}

void init2() {
	for (int i=1;i<512;i++) {
		ans[i]=f(i);
	}
}

int main () {
	init();
	init2();
	int q;
	scanf("%d",&q);
	long long x;
	while (q--) {
		scanf("%lld",&x);
		printf("%d\n",(x>=512)?-1:ans[x]);
	}
	return 0;
}
