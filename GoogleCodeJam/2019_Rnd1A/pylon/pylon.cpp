#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int step2[2] = {-2, 3};
int step3[3] = {1, 2, -2};

void ei(int r, int c, bool rev) {
	if (rev) printf("%d %d %d %d\n", c, r, c + r, c - r);
	else printf("%d %d %d %d\n", r, c, r + c, r - c);
}

void print2(int r, int w, bool rev) {
	int cr = 1;
	int cc = 0;
	ei(r + cr + 1, cc + 1, rev);
	for (int i = 1; i < 2 * w; i++) {
		cr++;
		cc += step2[i % 2];
		cr %= 2;
		cc = (cc % w + w) % w;
		ei(r + cr + 1, cc + 1, rev);
	}
}

void print3(int r, int w, bool rev) {
	fflush(stdout);
	int cr = 0;
	int cc = 0;
	ei(r + cr + 1, cc + 1, rev);
	for (int i = 1; i < 3 * w; i++) {
		cr++;
		cc += step3[i % 3];
		cr %= 3;
		cc = (cc % w + w) % w;
		ei(r + cr + 1, cc + 1, rev);
	}
}

void print(int h, int w) {
	if (h == 0) return;
	if (h % 2) {
		print(h - 3, w);
		print3(h - 3, w, false);
	} else {
		print(h - 2, w);
		print2(h - 2, w, false);
	}
}

void f() {
	int r, c;
	scanf("%d%d", &r, &c);
	if (c >= 5) {
		printf("POSSIBLE\n");
		print(r, c);
	} else if (c == 4 && r % 3 == 0) {
		printf("POSSIBLE\n");
		for (int i = 0; i < r; i += 3) {
			print3(i, c, false);
		}
	} else if (c == 3 && r >= 4) {
		printf("POSSIBLE\n");
		print3(0, r, true); // reverse
	} else if (c == 2 && r >= 5) {
		printf("POSSIBLE\n");
		print2(0, r, true);
	} else {
		printf("IMPOSSIBLE\n");
	}
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
