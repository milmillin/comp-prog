#include <cstdio>
#include <cstring>

using namespace std;

bool neg[3010];

void f() {
	memset(neg,0,sizeof(neg));
	int n,k;
	scanf("%d%d",&n,&k);
	int sum=n*(n+1)/2;
	int rmd=sum-k;
	//printf("-- %d\n",rmd);
	if (rmd%2||rmd/2>=sum) {
		printf("Impossible\n");
		return;
	}
	rmd/=2;
	for (int i=n;i>1;i--) {
		if (rmd>=i&&rmd-i!=1) {
			neg[i]=true;
			rmd-=i;
		}
	}
	if (rmd) {
		printf("Impossible\n");
		return;
	}
	printf("1");
	for (int i=2;i<=n;i++) {
		if (neg[i]) printf("-");
		else printf("+");
		printf("%d",i);
	}
	printf("\n");
}

int main () {
	for (int i=0;i<10;i++) {
		f();
	}
	return 0;
}
