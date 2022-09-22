#include <cstdio>

using namespace std;

int cnt[12];

int main () {
	cnt[2]=4;
	cnt[3]=4;
	cnt[4]=4;
	cnt[5]=4;
	cnt[6]=4;
	cnt[7]=4;
	cnt[8]=4;
	cnt[9]=4;
	cnt[10]=12;
	cnt[11]=4;

	int n;
	scanf("%d",&n);
	int x;
	int sum=21;
	for (int i=0;i<n;i++) {
		scanf("%d",&x);
		cnt[x]--;
		sum-=x;
	}
	int rmd=0;
	for (int i=sum;i<=11;i++) {
		rmd+=cnt[i];
	}
	int xx=0;
	for (int i=1;i<=sum;i++) {
		xx+=cnt[i];
	}
	if (rmd>=xx) {
		printf("DOSTA\n");
	} else {
		printf("VUCI\n");
	}
	return 0;
}
