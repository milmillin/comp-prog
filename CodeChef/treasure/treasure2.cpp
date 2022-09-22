#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 1000000007;

void f() {
	int r, c;
	scanf("%d%d", &r, &c);
	vector<vector<int>> tbl(r + 2, vector<int>(c, 0));
	int x;
	for (int i = 1; i <= r; i++) {
		for (int j = 0; j < c; j++) {
			scanf("%d", &x);
			if (x == -1) tbl[i][j] = 2;
			else tbl[i][j] = 1;
		}
	}
	for (int j = 0; j < c; j++) {
		tbl[0][j] = 2;
		tbl[r + 1][j] = 2;
	}
	long long ans = 1;
	for (int i = 1; i <= r; i++) {
		for (int j = 0; j < c; j++) {
			ans *= min(tbl[i - 1][j], tbl[i + 1][j]);
			ans %= mod;
		}
	}
	printf("%lld\n", ans);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}
