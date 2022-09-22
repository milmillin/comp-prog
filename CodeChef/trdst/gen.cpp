#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<int> pth[100100];

int n = 100000;
int cur = 1;

void dfs(int idx, bool isroot) {
	int cnt;
	if (isroot) {
		cnt = rand() % (n - cur) + 1;
	} else {
		cnt = rand() % (n - cur + 1);
	}
	fprintf(stderr, "%d: %d, %d;  ", idx, cnt, cur);
	for (int i = 0; i < cnt; i++) {
		pth[idx].push_back(cur++);
	}
	for (auto i : pth[idx]) {
		dfs(i, false);
	}
}


int main () {
	srand(time(NULL));
	printf("%d\n", n);
	for (int i = 1; i <= n; i++) {
		printf("%d ", rand() % (n - 1) + 1);
	}
	printf("\n");
	dfs(0, true);
	for (int i = 0; i < n; i++) {
		for (auto j : pth[i]) {
			printf("%d %d\n", i + 1, j + 1);
		}
	}
}
