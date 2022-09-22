#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

int n;
int ans[50100];
bool solvable[50100];

void init() {
	solvable[0] = true;
	solvable[4] = true;
	solvable[5] = true;
	solvable[7] = true;
	for (int i = 8; i < 50100; i++) {
		if (solvable[i - 4] || solvable[i - 5] || solvable[i - 7]) {
			solvable[i] = true;
		}
	}
}

int _ask(int a,int b,int c) {
	printf("1 %d %d %d\n", a + 1, b + 1, c + 1);
	fflush(stdout);
	int res;
	scanf("%d", &res);
	return res;
}

int ask(int a, int sz, int off) {
	return _ask(off + (a % sz), off + ((a + 1) % sz), off + ((a + 2) % sz));
}

void solve4(int idx) {
	vector<int> tbl(4, 0);
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		tbl[i] = ask(i + 1, 4, idx);
		sum ^= tbl[i];
	}
	for (int i = 0; i < 4; i++) {
		ans[idx + i] = tbl[i] ^ sum;
	}
}

void solve5(int idx) {
	vector<int> tbl(5, 0);
	int sum = 0;
	for (int i = 0; i < 5; i++) {
		tbl[i] = ask(i + 1, 5, idx);
		sum ^= tbl[i];
	}
	for (int i = 0; i < 5; i++) {
		ans[(i + 1) % 5 + idx] = sum ^ tbl[i] ^ tbl[(i + 3) % 5];
	}
}

void solve7(int idx) {
	vector<int> tbl(7, 0);
	int sum = 0;
	for (int i = 0; i < 7; i++) {
		tbl[i] = ask(i + 1, 7, idx);
		sum ^= tbl[i];
	}
	for (int i = 0; i < 7; i++) {
		ans[i + idx] = sum ^ tbl[i] ^ tbl[(i + 3) % 7];
	}
}

void solve(int nn) {
	if (nn == 0) return;
	if (solvable[nn - 7]) {
		solve7(nn - 7);
		solve(nn - 7);
	} else if (solvable[nn - 5]) {
		solve5(nn - 5);
		solve(nn - 5);
	} else if (solvable[nn - 4]) {
		solve4(nn - 4);
		solve(nn - 4);
	} else {
		assert(false);
	}	
}

int answer() {
	printf("2 ");
	for (int i = 0; i < n; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	fflush(stdout);
	int res;
	scanf("%d", &res);
	return res;
}
void f() {
	memset(ans, 0, sizeof(ans));
	scanf("%d", &n);
	solve(n);
	assert(answer() == 1);
}

int main() {
	init();
	int q;
	scanf("%d", &q);
	while (q--) {
		f();
	}
	return 0;
}
