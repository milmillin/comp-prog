#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int ask(int x, int y) {
	printf("Q %d %d\n", x, y);
	fflush(stdout);
	int res;
	scanf("%d", &res);
	return res;
}

bool answer(int x1, int y1, int x2, int y2) {
	printf("A %d %d %d %d\n", x1, y1, x2, y2);
	fflush(stdout);
	int res;
	scanf("%d", &res);
	return res == 1;
}

const int mx = 1000000000;

void f() {
	int a = ask(0, 0);
	int b = ask(mx, 0);
	int mid = (a + mx - b) / 2;
	int top = ask(mid, 0);
	int bot = ask(mid, mx);
	bot = mx - bot;
	int left = ask(0, top);
	int right = ask(mx, top);
	right = mx - right;
	answer(left, top, right, bot);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) f();
	return 0;
}
