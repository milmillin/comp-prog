#include <cstdio>
#include <algorithm>

using namespace std;

void f() {
	int n, p;
	scanf("%d%d", &n, &p);
	int m = n % (n / 2 + 1);
	if (m == 0) {
		printf("%lld\n", (long long)p * p * p);
		return;
	}
	long long pm = p - m;
	long long pn = p - n;
	printf("%lld\n", pm * pm + pm * pn + pn * pn);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
	return 0;
}
