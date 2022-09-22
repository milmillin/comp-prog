#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int curday() {
	int x;
	scanf("%d", &x);
	return x;
}

void add(int pos, int num) {
	printf("%d %d\n", pos, num);
	fflush(stdout);
}
	

bool f() {
	for (int i = 0; i < 99; i++) {
		if (curday() == -1) return false;
		add(i % 19 + 1, i + 1);
	}
	if (curday() == -1) return false;
	add(20, 100);
}

int main () {
	int q;
	scanf("%d", &q);
	while (q--) {
		if (!f()) return 0;
	}
	returrn 0;
}
