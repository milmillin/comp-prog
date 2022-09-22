#include <cstdio>
#include <algorithm>

using namespace std;

int tbl[1000100];
int n,t;

int op(int zero,int one) {
	if (one==0) {
		for (int i=0;i<zero;i++) printf("0 ");
		return zero;
	}
	if (zero==0) {
		for (int i=0;i<one;i++) printf("1 ");
		return 0;
	}
	if (t<=zero) {
		for (int i=0;i<zero-t;i++) printf("0 ");
		zero=t;
		printf("1 ");
		one--;
		for (int i=0;i<one;i++) {
			if (zero) {
				printf("0 ");
				zero--;
			}
			printf("1 ");
		}
		return zero;
	}
	
	printf("1 ");
	one--;
	int times = min(one,t-zero);
	for (int i=0;i<times;i++) {
		printf("1 ");
		one--;
	}
	for (int i=0;i<one;i++) {
		if (zero) {
			printf("0 ");
			zero--;
		}
		printf("1 ");
	}
	return zero;
}

int main () {
	scanf("%d%d",&n,&t);
	
	for (int i=0;i<n;i++) {
		scanf("%d",&tbl[i]);
	}
	int cur=0;
	int zr=0;
	int on=0;
	while (cur<n) {
		while (tbl[cur]==0) {
			cur++;
			zr++;
		}
		while (tbl[cur]==1) {
			cur++;
			on++;
		}
		zr=op(zr,on);
		on=0;
	}
	printf("\n");
	return 0;
}
