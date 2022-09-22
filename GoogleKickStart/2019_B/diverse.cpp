#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int add(vector<int> &cnt, int val, int s) {
	int cur = 0;
	if (cnt[val] <= s) cur++;
	cnt[val]++;
	if (cnt[val] == s + 1) {
		cur -= cnt[val];
	}
	return cur;
}

int rem(vector<int> &cnt, int val, int s) {
	int cur = 0;
	if (cnt[val] <= s) cur--;
	cnt[val]--;
	if (cnt[val] == s) {
		cur += s;
	}
	return cur;
}

void f() {
	int n, s;
	scanf("%d%d", &n, &s);
	vector<int> tbl(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &tbl[i]);
	}
	vector<int> cnt(100001, 0);
	int mx = 0;
	for (int sz = 1; sz <= n; sz++) {
		int cur = 0;
		for (int i = 0; i < sz; i++) {
			cur += add(cnt, tbl[i], s);
		}
		mx = max(mx, cur);
		for (int i = sz; i < n; i++) {
			cur += add(cnt, tbl[i], s);
			cur += rem(cnt, tbl[i - sz], s);
			mx = max(mx, cur);
		}
		for (int i = 0; i < sz; i++) {
			cur += rem(cnt, tbl[n - i - 1], s);
		}
	}
	printf("%d\n", mx);
	fflush(stdout);
}


int main () {
	int q;
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		printf("Case #%d: ", i);
		f();
	}
	return 0;
}
