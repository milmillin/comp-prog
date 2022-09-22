#include <cstdio>
#include <cassert>

int tbl[20];

void solve12() {
	int n;
	scanf("%d",&n);
	assert(n<=6);
	int x=0;
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
		x^=tbl[i];
	}	
	for (int i=0;i<n;i++) {
		for (int j=i+1;j<n;j++) {
			if ((tbl[i]^tbl[j])==x) {
				printf("%d %d\n",tbl[i],tbl[j]);
				return;
			}
		}
	}
	printf("0 0\n");
	//assert(false);
}

void solve3() {
	int n;
	scanf("%d",&n);
	assert(n<=6);
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	int x=0;
	for (int i=0;i<2*n+1;i++) {
		x^=i;
	}
	x=x^a^b^c^d;
	printf("%d\n",x);
}

int main () {
	int t;
	scanf("%d",&t);
	int s;
	scanf("%d",&s);
	for (int i=0;i<t;i++) {
		if (s==1||s==2) {
			solve12();
		} else {
			solve3();
		}
	}
	return 0;
}
