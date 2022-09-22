#include <cstdio>
#include <algorithm>

using namespace std;

bool test(int x) {
	printf("1 %d\n", x);
	fflush(stdout);
	int res;
	scanf("%d", &res);
	return res == 0;
}

void ans(int x) {
	printf("3 %d\n", x);
	fflush(stdout);
}

void repair() {
	printf("2\n");
	fflush(stdout);
}

int main () {
	int N, c;
	scanf("%d%d", &N, &c);
	int inc = 849;
	int cur = min(850, N);
	int last = 0;
	while (test(cur)) {
		if (cur == N) {
			ans(cur);
			return 0;
		}
		last = cur;
		cur += inc;
		cur = min(cur, N);
		inc--;
	}
	repair();
	for (int i = last + 1; i <= cur; i++) {
		if (!test(i)) {
			ans(i);
			return 0;
		}
	}
	return 0;
}
