#include <cstdio>

using namespace std;

void f(int x) {
	int opcnt=0;
	if (x==0) {
		printf("ZER X\n"),opcnt++;
		printf("PRN A\n"),opcnt++;
	} else {
		int i=0;
		int cnt=0;
		while (x) {
			if (i==0) printf("ONE X\n"),opcnt++;
			else printf("POP X\n"),opcnt++;
			if (x==1) cnt++;
			if (x!=1) {
				if (x%2) cnt++,printf("PUH X\n"),opcnt++;
				printf("PUH X\nPUH X\nADD X\n"),opcnt++,opcnt++,opcnt++;
			}
			i++;
			x>>=1;
		}
		printf("PUH X\n"),opcnt++;
		for (int j=1;j<cnt;j++) {
			printf("ADD X\n"),opcnt++;
		}
		if (cnt>1) printf("POP X\n"),opcnt++;
		printf("PRN X\n"),opcnt++;
	}
	//printf("--> %d\n",opcnt);
}

int main () {
	int x;
	while (scanf("%d",&x)!=EOF) {
		f(x);
	}
	return 0;
}
