#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

vector<int> prime = {3,5,7,11,13,17,18};

int get(int x) {
	for (int i = 0; i < 18; i++) {
		printf("%d ", x);
	}
	printf("\n");
	fflush(stdout);
	int sum = 0;
	int tmp;
	for (int i = 0; i < 18; i++) {
		scanf("%d", &tmp);
		assert(tmp >= 0);
		sum += tmp;
	}
	sum %= x;
	return sum;
}

void f() {
	vector<int> cnt(1000001, 0);
	for (auto p : prime) {
		int res = get(p);
		for (int i = res; i <= 1000000; i += p) {
			cnt[i]++;
		}
	}
	int mx = -1;
	int id = -1;
	for (int i = 1; i <= 1000000; i++) {
		if (cnt[i] > mx) {
			mx = cnt[i];
			id = i;
		}
	}
	printf("%d\n", id);
	fflush(stdout);
	int verdict;
	scanf("%d", &verdict);
	assert(verdict == 1);
}

int main () {
	int t, n, m;
	scanf("%d%d%d", &t, &n, &m);
	while (t--) f();
	return 0;
}
