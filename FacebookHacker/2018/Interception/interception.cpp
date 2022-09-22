#include <cstdio>
#include <algorithm>

using namespace std;

void f() {
	int n;
	scanf("%d",&n);
	int x;
	for (int i=0;i<=n;i++) {
		scanf("%d",&x);
	}
	if (n%2) {
		printf("1\n0.0\n");
	} else {
		printf("0\n");
	}
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
