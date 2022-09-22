#include <cstdio>

using namespace std;

void f() {
	int n;
	scanf("%d",&n);
	if (n==1||n==2||n==3||n==5||n==7||n==11) {
		printf("-1\n");
		return;
	}
	if (n%4==0||n%4==2) {
		printf("%d\n",n/4);
		return;
	} else if (n%4==1||n%4==3) {
		printf("%d\n",n/4-1);	
		return;
	}
}

int main () {
	int q;
	scanf("%d",&q);
	while (q--) f();
	return 0;
}
