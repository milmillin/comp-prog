#include <cstdio>
#include <algorithm>

using namespace std;

void f() {
	int d,n;
	scanf("%d%d",&d,&n);
	int k,s;
	double mintime=0;
	for (int i=0;i<n;i++) {
		scanf("%d%d",&k,&s);
		mintime=max(mintime,(double)(d-k)/s);
	}
	printf("%f\n",d/mintime);
}

int main () {
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) {
		printf("Case #%d: ",i);
		f();
	}
	return 0;
}
