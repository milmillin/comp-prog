#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <map>

using namespace std;

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}


void f() {
	int n, l;
	scanf("%d%d", &n, &l);
	assert(n <= 10000);
	vector<int> tbl(l);
	vector<int> ans(l + 1);
	for (int i = 0; i < l; i++) {
		scanf("%d", &tbl[i]);
	}
	int index = -1;
	for (int i = 0; i < l - 1; i++) {
		if (tbl[i] != tbl[i + 1]) {
			ans[i + 1] = gcd(tbl[i], tbl[i + 1]);
			index = i + 1;
			break;
		}
	}

	for (int i = index + 1; i <= l; i++) {
		ans[i] = tbl[i - 1] / ans[i - 1];
	}
	for (int i = index - 1; i >= 0; i--) {
		ans[i] = tbl[i] / ans[i + 1];
	}

	map<int, char> map;
	for (auto i : ans) {
		map[i];
	}

	char x = 'A';
	for (auto &i : map) {
		i.second = x++;
	}

	for (int i = 0; i <= l; i++) {
		printf("%c", map[ans[i]]);
	}
	printf("\n");
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
