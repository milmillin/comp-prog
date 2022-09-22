#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

void f() {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<int> tbl(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &tbl[i]);
	}
	vector<long long> qs(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		int limit = (int)sqrt(tbl[i]);
		for (int j = 1; j <= limit; j++) {
			int res = tbl[i] / j;
			if (i - j < 0) break;
			qs[i - j] += res;
			if (i - j - 1 >= 0) qs[i - j - 1] -= res;
		}
		int resStart = tbl[i] / limit;
		for (int res = resStart; res > 0; res--) {
			int jmin = tbl[i] / (res + 1) + 1;
			int jmax = tbl[i] / res;
			jmin = max(jmin, limit + 1);
			if (jmin > jmax) continue;
			if (i - jmin < 0) break;
			qs[i - jmin] += res;
			if (i - jmax - 1 >= 0) qs[i - jmax - 1] -= res;
		}
	}
	long long cur = 0;
	int mn = n;
	for (int i = n; i >= 0; i--) {
		cur += qs[i];
		qs[i] = cur;
		if (qs[i] <= k) mn = i;
	}
	printf("%d\n", mn + 1);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}
